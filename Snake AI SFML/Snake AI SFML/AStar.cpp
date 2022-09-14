#include "AStar.h"
#include "CocktailSorter.h"

#include <math.h>

AStar::AStar(GridLocation _startNode, GridLocation _goalNode, GameArea& _area, std::vector<std::vector<SnakePart>>& _snakeClones) :
	open(),
	closed(),
	startNode(_startNode, 0, 0, 0, nullptr),
	goalNode(_goalNode, 0, 0, 0, nullptr),
	lastPos(startNode),
	stillSearching(true),
	foundPath(false),
	moves()
{
	open.push_back(startNode);

	do
	{
		Search(lastPos, _area, _snakeClones);
	} while(stillSearching);

	if(foundPath)
		GetPath(&lastPos, _area);
}

AStar::~AStar()
{
	for(PathMarker marker : open)
	{
		delete marker.GetParent();
	}

	for(PathMarker marker : closed)
	{
		delete marker.GetParent();
	}
}

void AStar::Search(PathMarker& _playerNode, GameArea& _area, std::vector<std::vector<SnakePart>>& _snakeClones)
{
	if(_playerNode.Equals(goalNode)) // Found the best path
	{
		stillSearching = false;
		foundPath = true;
		return;
	}

	for(GridLocation dir : directions)
	{
		GridLocation neighbourNode = dir.Add(_playerNode.GetLocation());

		int currentSnake = 0;
		for(int i = 0; i < _snakeClones.size(); i++)
		{
			// Finds the current position and makes a copy to move
			if(_snakeClones[i][0].GetLocation().ToVector() == _playerNode.GetLocation().ToVector())
			{
				_snakeClones.push_back(std::vector<SnakePart>(_snakeClones[i]));
				MoveSnakeClone(dir, _area, _snakeClones[_snakeClones.size() - 1]);
				currentSnake = i;
				break;
			}
		}

		// If the 'neighbourNode' is outside of the game area
		if(neighbourNode.GetX() <= 0 || neighbourNode.GetX() > _area.GetGridSize() ||
			neighbourNode.GetY() <= 0 || neighbourNode.GetY() > _area.GetGridSize())
		{
			continue;
		}

		if(IsClosed(neighbourNode))
			continue;

		bool hitsItself = false;
		for(SnakePart part : _snakeClones[currentSnake])
		{
			// If the 'neighbourNode' is one the snake
			if(!neighbourNode.Equals(startNode.GetLocation()) && neighbourNode.Equals(part.GetLocation()))
			{
				std::vector<SnakePart> tempSnakeClone = _snakeClones[currentSnake];
				// Ignores the tail of the snake is longer than 3 unless it is the first move after eating the food
				if(tempSnakeClone.size() > 3 && closed.size() <= 4 || !neighbourNode.Equals(tempSnakeClone[tempSnakeClone.size() - 1].GetLocation()))
				{
					hitsItself = true;
					break;
				}
				// Doesn't ignore the tail if the snake is shorter or equal to 3
				else if(tempSnakeClone.size() <= 3)
				{
					hitsItself = true;
					break;
				}
			}
		}

		if(hitsItself)
			continue;

		// Distance between 'startNode' and 'neighbourNode'
		float G = abs(_playerNode.GetLocation().GetX() - neighbourNode.GetX()) + abs(_playerNode.GetLocation().GetY() - neighbourNode.GetY()) + _playerNode.GetG();
		// Distance between 'neighbourNode' and 'goalNode'
		float H = (float)abs(neighbourNode.GetX() - goalNode.GetLocation().GetX()) + abs(neighbourNode.GetY() - goalNode.GetLocation().GetY());
		// The sum of G and H which also is the distance between the 'startNode' and the 'goalNode'
		float F = G + H;

		if(!UpdateMarker(neighbourNode, G, H, F, &_playerNode))
		{
			PathMarker* node = new PathMarker(_playerNode);
			open.push_back(PathMarker(neighbourNode, G, H, F, node));
		}
	}

	if(open.size() == 0)
	{
		stillSearching = false;
		foundPath = false;
		return;
	}

	CocktailSorter sorter(open);
	sorter.Update();

	PathMarker pm = open.front();
	closed.push_back(pm);
	open.erase(open.begin());

	lastPos = pm;
}

bool AStar::UpdateMarker(GridLocation _position, float _g, float _h, float _f, PathMarker* _parent)
{
	for(PathMarker marker : open)
	{
		if(marker.GetLocation().Equals(_position))
		{
			marker.Update(_g, _h, _f, _parent);
			return true;
		}
	}

	return false;
}

bool AStar::IsClosed(GridLocation _location)
{
	for(PathMarker marker : closed)
	{
		if(marker.GetLocation().Equals(_location))
			return true;
	}

	return false;
}

void AStar::GetPath(PathMarker* _lastPos, GameArea& _area)
{
	PathMarker* path = _lastPos;

	while(path && !path->Equals(startNode))
	{
		if(path->GetLocation().GetX() > path->GetParent()->GetLocation().GetX())
		{
			moves.push_back(PathMarker(dir.Right, path->GetLocation(), _area));
		}
		else if(path->GetLocation().GetX() < path->GetParent()->GetLocation().GetX())
		{
			moves.push_back(PathMarker(dir.Left, path->GetLocation(), _area));
		}
		else if(path->GetLocation().GetY() > path->GetParent()->GetLocation().GetY())
		{
			moves.push_back(PathMarker(dir.Up, path->GetLocation(), _area));
		}
		else if(path->GetLocation().GetY() < path->GetParent()->GetLocation().GetY())
		{
			moves.push_back(PathMarker(dir.Down, path->GetLocation(), _area));
		}

		path = path->GetParent();
	}
}

void AStar::MoveSnakeClone(GridLocation _moveDirection, GameArea& _area, std::vector<SnakePart>& _snakeClone)
{
	for(int i = (int)_snakeClone.size() - 1; i > 0; i--)
	{
		_snakeClone[i].Move(_snakeClone[i - 1].GetLocation(), _area);
	}
	_snakeClone[0].Move(_moveDirection, _area);
}
