#include "HamiltonianCycle.h"
#include "AStar.h"

HamiltonianCycle::HamiltonianCycle()
{
}

void HamiltonianCycle::GetMoves(Snake _snake, GameArea& _area, std::vector<Snake>& _snakeClones, std::vector<PathMarker>& _moves)
{
	AStar aStarTail(_snake.GetHead().GetLocation(), _snake.GetTail().GetLocation(), _area, _snakeClones);
	_moves = aStarTail.GetMoves();

	ExtendPath(_moves, _snake, _area); //TODO Make Faster
}

void HamiltonianCycle::ExtendPath(std::vector<PathMarker>& _moves, Snake& _snakeClone, GameArea& _area)
{
	Directions directions;

	std::vector<PathMarker> movesCopy;
	movesCopy.push_back(PathMarker(_snakeClone.GetHead().GetLocation(), _area));
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
				i = 1;
				extended = true;
			}
			else if(!currentDown.isVisited && !nextDown.isVisited)
			{
				movesCopy.erase(movesCopy.begin() + i);
				movesCopy.insert(movesCopy.begin() + i, PathMarker(currentDown.location.Add(dir.Add(directions.Up)), _area));
				movesCopy.insert(movesCopy.begin() + i, PathMarker(currentDown.location.Add(dir), _area));
				movesCopy.insert(movesCopy.begin() + i, PathMarker(currentDown.location, _area));
				i = 1;
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
				i = 1;
				extended = true;
			}
			else if(!currentLeft.isVisited && !nextLeft.isVisited)
			{
				movesCopy.erase(movesCopy.begin() + i);
				movesCopy.insert(movesCopy.begin() + i, PathMarker(PathMarker(currentLeft.location.Add(dir.Add(directions.Right)), _area)));
				movesCopy.insert(movesCopy.begin() + i, PathMarker(PathMarker(currentLeft.location.Add(dir), _area)));
				movesCopy.insert(movesCopy.begin() + i, PathMarker(currentLeft.location, _area));
				i = 1;
				extended = true;
			}
		}

		if(!extended)
			i++;
	}

	_moves.clear();
	if(movesCopy.size() > 1)
	{
		_moves = movesCopy;
		_moves.erase(_moves.begin());
		movesCopy.clear();
		for(int i = (int)_moves.size() - 1; i >= 0; i--)
		{
			movesCopy.push_back(_moves[i]);
		}

		_moves = movesCopy;
	}
}

void HamiltonianCycle::IsVisited(Node& _cUpRight, Node& _nUpRight, Node& _cDownLeft, Node& _nDownLeft, std::vector<PathMarker>& _movesCopy)
{
	if(std::find(_movesCopy.begin(), _movesCopy.end(), _cUpRight.location) != _movesCopy.end())
		_cUpRight.isVisited = true;
	if(std::find(_movesCopy.begin(), _movesCopy.end(), _nUpRight.location) != _movesCopy.end())
		_nUpRight.isVisited = true;
	if(std::find(_movesCopy.begin(), _movesCopy.end(), _cDownLeft.location) != _movesCopy.end())
		_cDownLeft.isVisited = true;
	if(std::find(_movesCopy.begin(), _movesCopy.end(), _nDownLeft.location) != _movesCopy.end())
		_nDownLeft.isVisited = true;
}

void HamiltonianCycle::IsOnSnake(Node& _cUpRight, Node& _nUpRight, Node& _cDownLeft, Node& _nDownLeft, Snake& _snakeClone)
{
	if(std::find(_snakeClone.GetSnake().begin() + 1, _snakeClone.GetSnake().end() - 1, _cUpRight.location) != _snakeClone.GetSnake().end() - 1)
		_cUpRight.isVisited = true;
	if(std::find(_snakeClone.GetSnake().begin() + 1, _snakeClone.GetSnake().end() - 1, _nUpRight.location) != _snakeClone.GetSnake().end() - 1)
		_nUpRight.isVisited = true;
	if(std::find(_snakeClone.GetSnake().begin() + 1, _snakeClone.GetSnake().end() - 1, _cDownLeft.location) != _snakeClone.GetSnake().end() - 1)
		_cDownLeft.isVisited = true;
	if(std::find(_snakeClone.GetSnake().begin() + 1, _snakeClone.GetSnake().end() - 1, _nDownLeft.location) != _snakeClone.GetSnake().end() - 1)
		_nDownLeft.isVisited = true;
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