#include "HamiltonianCycle.h"
#include "AStar.h"

HamiltonianCycle::HamiltonianCycle(std::vector<SnakePart> _snake, GameArea& _area, std::vector<std::vector<SnakePart>>& _snakeClones)
{
	AStar aStarTail(_snake[0].GetLocation(), _snake[_snake.size() - 1].GetLocation(), _area, _snakeClones);

	moves = aStarTail.GetMoves();
	ExtendPath(moves, _snake, _area);
}

void HamiltonianCycle::ExtendPath(std::vector<PathMarker>& _moves, std::vector<SnakePart>& _snakeClone, GameArea& _area)
{
	Directions directions;

	std::vector<PathMarker> movesCopy;
	movesCopy.push_back(PathMarker(_snakeClone[0].GetLocation(), _area));
	for(int i = (int)_moves.size() - 1; i >= 0; i--)
	{
		movesCopy.push_back(_moves[i]);
	}

	for(int i = 1; i < movesCopy.size();)
	{
		bool extended = false;

		GridLocation dir = movesCopy[i - 1].GetLocation().GetDirectionTo(movesCopy[i].GetLocation());

		if(dir.GetX() != 0)
		{
			Node currentUp;
			currentUp.location = movesCopy[i - 1].GetLocation().Add(directions.Up);
			Node nextUp;
			nextUp.location = movesCopy[i].GetLocation().Add(directions.Up);
			Node currentDown;
			currentDown.location = movesCopy[i - 1].GetLocation().Add(directions.Down);
			Node nextDown;
			nextDown.location = movesCopy[i].GetLocation().Add(directions.Down);

			IsVisited(currentUp, nextUp, currentDown, nextDown, movesCopy);
			IsOutsideGameArea(currentUp, nextUp, currentDown, nextDown, _area);
			IsOnSnake(currentUp, nextUp, currentDown, nextDown, _snakeClone);

			if(!currentUp.isVisited && !nextUp.isVisited)
			{
				movesCopy.erase(movesCopy.begin() + i);
				movesCopy.insert(movesCopy.begin() + i, PathMarker(currentUp.location.Add(dir.Add(directions.Down)), _area));
				movesCopy.insert(movesCopy.begin() + i, PathMarker(currentUp.location.Add(dir), _area));
				movesCopy.insert(movesCopy.begin() + i, PathMarker(currentUp.location, _area));
				extended = true;
			}
			else if(!currentDown.isVisited && !nextDown.isVisited)
			{
				movesCopy.erase(movesCopy.begin() + i);
				movesCopy.insert(movesCopy.begin() + i, PathMarker(currentDown.location.Add(dir.Add(directions.Up)), _area));
				movesCopy.insert(movesCopy.begin() + i, PathMarker(currentDown.location.Add(dir), _area));
				movesCopy.insert(movesCopy.begin() + i, PathMarker(currentDown.location, _area));
				extended = true;
			}
		}
		else if(dir.GetY() != 0)
		{
			Node currentRight;
			currentRight.location = movesCopy[i - 1].GetLocation().Add(directions.Right);
			Node nextRight;
			nextRight.location = movesCopy[i].GetLocation().Add(directions.Right);
			Node currentLeft;
			currentLeft.location = movesCopy[i - 1].GetLocation().Add(directions.Left);
			Node nextLeft;
			nextLeft.location = movesCopy[i].GetLocation().Add(directions.Left);

			IsVisited(currentRight, nextRight, currentLeft, nextLeft, movesCopy);
			IsOutsideGameArea(currentRight, nextRight, currentLeft, nextLeft, _area);
			IsOnSnake(currentRight, nextRight, currentLeft, nextLeft, _snakeClone);

			if(!currentRight.isVisited && !nextRight.isVisited)
			{
				movesCopy.erase(movesCopy.begin() + i);
				movesCopy.insert(movesCopy.begin() + i, PathMarker(PathMarker(currentRight.location.Add(dir.Add(directions.Left)), _area)));
				movesCopy.insert(movesCopy.begin() + i, PathMarker(PathMarker(currentRight.location.Add(dir), _area)));
				movesCopy.insert(movesCopy.begin() + i, PathMarker(currentRight.location, _area));
				extended = true;
			}
			else if(!currentLeft.isVisited && !nextLeft.isVisited)
			{
				movesCopy.erase(movesCopy.begin() + i);
				movesCopy.insert(movesCopy.begin() + i, PathMarker(PathMarker(currentLeft.location.Add(dir.Add(directions.Right)), _area)));
				movesCopy.insert(movesCopy.begin() + i, PathMarker(PathMarker(currentLeft.location.Add(dir), _area)));
				movesCopy.insert(movesCopy.begin() + i, PathMarker(currentLeft.location, _area));
				extended = true;
			}
		}

		if(!extended)
			i++;
	}

	moves.clear();
	if(movesCopy.size() > 1)
	{
		for(int i = 1; i < movesCopy.size(); i++)
		{
			moves.insert(moves.begin(), movesCopy[i]);
		}
	}
}

void HamiltonianCycle::IsVisited(Node& _cUpRight, Node& _nUpRight, Node& _cDownLeft, Node& _nDownLeft, std::vector<PathMarker>& _movesCopy)
{
	for(PathMarker marker : _movesCopy)
	{
		if(marker.GetLocation().Equals(_cUpRight.location))
			_cUpRight.isVisited = true;
		if(marker.GetLocation().Equals(_nUpRight.location))
			_nUpRight.isVisited = true;
		if(marker.GetLocation().Equals(_cDownLeft.location))
			_cDownLeft.isVisited = true;
		if(marker.GetLocation().Equals(_nDownLeft.location))
			_nDownLeft.isVisited = true;
	}
}

void HamiltonianCycle::IsOnSnake(Node& _cUpRight, Node& _nUpRight, Node& _cDownLeft, Node& _nDownLeft, std::vector<SnakePart>& _snakeClone)
{
	for(int j = 1; j < _snakeClone.size() - 1; j++)
	{
		if(_snakeClone[j].GetLocation().Equals(_cUpRight.location))
			_cUpRight.isVisited = true;
		if(_snakeClone[j].GetLocation().Equals(_nUpRight.location))
			_nUpRight.isVisited = true;
		if(_snakeClone[j].GetLocation().Equals(_cDownLeft.location))
			_cDownLeft.isVisited = true;
		if(_snakeClone[j].GetLocation().Equals(_nDownLeft.location))
			_nDownLeft.isVisited = true;
	}
}

void HamiltonianCycle::IsOutsideGameArea(Node& _cUpRight, Node& _nUpRight, Node& _cDownLeft, Node& _nDownLeft, GameArea& _area)
{
	if(_cUpRight.location.GetY() > _area.GetGridSize() || _cUpRight.location.GetX() > _area.GetGridSize())
		_cUpRight.isVisited = true;
	if(_nUpRight.location.GetY() > _area.GetGridSize() || _nUpRight.location.GetX() > _area.GetGridSize())
		_nUpRight.isVisited = true;
	if(_cDownLeft.location.GetY() <= 0 || _cDownLeft.location.GetX() <= 0)
		_cDownLeft.isVisited = true;
	if(_nDownLeft.location.GetY() <= 0 || _nDownLeft.location.GetX() <= 0)
		_nDownLeft.isVisited = true;
}