#include "AStar.h"
#include "CocktailSorter.h"

#include <math.h>

AStar::AStar(GridLocation _startNode, GridLocation _goalNode, GameArea& _area, std::vector<Snake>& _snakeClones) :
	open(),
	closed(),
	startNode(_startNode, 0, 0, 0, GridLocation()),
	goalNode(_goalNode, 0, 0, 0, GridLocation()),
	lastPos(startNode),
	stillSearching(true),
	foundPath(false),
	moves()
{
	open.push_back(startNode);

	// Avoid running into the tail by making it think it is 1 part longer than it actually is
	Snake& temp = _snakeClones[_snakeClones.size() - 1];
	temp.GetSnake().push_back(temp.GetSnake()[temp.GetSnake().size() - 1]);

	do
	{
		Search(lastPos, _area, _snakeClones);
	} while(stillSearching);

	if(foundPath)
		GetPath(lastPos.GetLocation(), _area);
}

void AStar::Search(PathMarker& _playerNode, GameArea& _area, std::vector<Snake>& _snakeClones)
{
	if(_playerNode.Equals(goalNode)) // Found the best path
	{
		stillSearching = false;
		foundPath = true;

		// Removes all snakeClones except the one that got the food
		Snake temp(SnakePart(goalNode.GetLocation()));
		auto it = std::find(_snakeClones.begin(), _snakeClones.end(), temp);
		int i = (int)std::distance(_snakeClones.begin(), it);

		if(i != _snakeClones.size())
		{
			std::vector<Snake> temps;
			temps.push_back(_snakeClones[i]);
			_snakeClones.clear();
			_snakeClones.push_back(temps[0]);
		}

		return;
	}

	for(GridLocation dir : directions)
	{
		GridLocation neighbourNode = dir.Add(_playerNode.GetLocation());

		sf::Clock clock;
		int currentSnake = 0;
		// Makes sure we don't move the snake when we look for the tail
		if(!_snakeClones[0].GetTail().GetLocation().Equals(goalNode.GetLocation()))
		{
			for(int i = 0; i < _snakeClones.size(); i++) //TODO Make Faster
			{
				// Finds the current position and makes a copy to move
				if(_snakeClones[i].GetHead().GetLocation().ToVector() == _playerNode.GetLocation().ToVector())
				{
					_snakeClones.push_back(Snake(_snakeClones[i]));
					MoveSnakeClone(dir, _area, _snakeClones[_snakeClones.size() - 1]);
					currentSnake = i;
					break;
				}
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

		if(!neighbourNode.Equals(startNode.GetLocation()))
		{
			SnakePart temp(GridLocation(neighbourNode.GetX(), neighbourNode.GetY()));

			// If the 'neighbourNode' is one the snake
			if(std::find(_snakeClones[currentSnake].GetSnake().begin(), _snakeClones[currentSnake].GetSnake().end(), temp) != _snakeClones[currentSnake].GetSnake().end())
			{
				if(currentSnake == 0 && !neighbourNode.Equals(goalNode.GetLocation()))
				{
					continue;
				}
				else if(currentSnake != 0)
				{
					continue;
				}
			}
		}


		// Distance between 'playerNode' and 'neighbourNode'
		float G = abs(_playerNode.GetLocation().GetX() - neighbourNode.GetX()) + abs(_playerNode.GetLocation().GetY() - neighbourNode.GetY()) + _playerNode.GetG();
		// Distance between 'neighbourNode' and 'goalNode'
		float H = (float)abs(neighbourNode.GetX() - goalNode.GetLocation().GetX()) + abs(neighbourNode.GetY() - goalNode.GetLocation().GetY());
		// The sum of G and H
		float F = G + H;

		if(!UpdateMarker(neighbourNode, G, H, F, _playerNode.GetLocation()))
			open.push_back(PathMarker(neighbourNode, G, H, F, _playerNode.GetLocation()));
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

bool AStar::UpdateMarker(GridLocation _position, float _g, float _h, float _f, GridLocation _parent)
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
	PathMarker temp(_location);
	if(std::find(closed.begin(), closed.end(), temp) != closed.end())
		return true;

	return false;
}

void AStar::GetPath(GridLocation _lastPos, GameArea& _area)
{
	GridLocation path = _lastPos;

	while(!path.Equals(GridLocation(0, 0)) && !path.Equals(startNode.GetLocation()))
	{
		GridLocation temp(path);
		auto it = std::find(closed.begin(), closed.end(), temp);
		int i = (int)std::distance(closed.begin(), it);

		if(i != closed.size())
		{
			moves.push_back(PathMarker(path, _area));
		}

		path = closed[i].GetParent();
	}
}

void AStar::MoveSnakeClone(GridLocation _moveDirection, GameArea& _area, Snake& _snakeClone)
{
	for(size_t i = _snakeClone.GetSnake().size() - 1; i > 0; i--)
	{
		_snakeClone.GetSnake()[i].Move(_snakeClone.GetSnake()[i - 1].GetLocation(), _area);
	}
	_snakeClone.GetHead().Move(_moveDirection, _area);
}