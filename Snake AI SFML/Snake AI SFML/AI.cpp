#include "AI.h"
#include "AStar.h"
#include "HamiltonianCycle.h"

#include <math.h>
#include <thread>

AI::AI() :
	moves(),
	snakeClone(),
	foundFastPath(false)
{
}

GridLocation AI::GetNextMove(std::vector<SnakePart> _snake, GridLocation _food, GameArea& _area)
{
	HamiltonianCycle hamiltonianCycle;
	std::vector<PathMarker> movesCopy;
	GridLocation move;
	snakeClone.clear();
	snakeClone.push_back(_snake);

	if(!foundFastPath)
	{
		// Find the shortest path to food unless the snake fills up 50% of the area
		if(_snake.size() <= _area.GetGridSize() * _area.GetGridSize() * .5f)
		{
			AStar aStarFood(_snake[0].GetLocation(), _food, _area, snakeClone);
			movesCopy = aStarFood.GetMoves();

			if(aStarFood.HasFoundPath() && _snake.size() >= 3)
			{
				std::vector<SnakePart> snakeCloneClone(snakeClone[0]);
				snakeCloneClone.push_back(snakeCloneClone[snakeCloneClone.size() - 1]); // Add 1 part because it has "eaten" the food

				snakeClone.clear();
				snakeClone.push_back(snakeCloneClone);

				// Check if longest path to tail exist
				std::vector<PathMarker> tempMoves;
				hamiltonianCycle.GetMoves(snakeCloneClone, _area, snakeClone, tempMoves);
				if(tempMoves.size() == 0)
					movesCopy.clear();
				else
					foundFastPath = true;
			}
			else if(aStarFood.HasFoundPath() && _snake.size() < 3)
				foundFastPath = true;
		}

		if(!foundFastPath)
		{
			//TODO Should be first in the function (Causes memory problems if it is, Multiple A*)
			// Find the longest path to tail
			std::vector<std::vector<SnakePart>> sSnakeClone;
			sSnakeClone.push_back(_snake);
			std::vector<PathMarker> sMovesCopy;
			std::thread hamiltonianCycleThread(&HamiltonianCycle::GetMoves, hamiltonianCycle, _snake, std::ref(_area), std::ref(sSnakeClone), std::ref(sMovesCopy));
			hamiltonianCycleThread.join();
			movesCopy = sMovesCopy;
		}

		// Choose a safe default move
		if(!foundFastPath && movesCopy.size() == 0)
			DefaultMove(move, _snake, _food, _area);

		moves = movesCopy;
	}

	if(moves.size() != 0)
	{
		move = _snake[0].GetLocation().GetDirectionTo(moves[moves.size() - 1].GetLocation());
		moves.erase(moves.end() - 1);

		if(moves.size() == 0)
			foundFastPath = false;
	}

	return move;
}

// Gets the move that gets the snake the furthest from the food and doesn't run into something
void AI::DefaultMove(GridLocation& _move, std::vector<SnakePart>& _snake, GridLocation& _food, GameArea& _area)
{
	int distance = 0;
	bool notUp = false;
	bool notDown = false;
	bool notRight = false;
	bool notLeft = false;
	Directions direction;
	for(SnakePart part : _snake)
	{
		if(!_snake[0].GetLocation().Add(direction.Up).Equals(part.GetLocation()) && !notUp &&
			_snake[0].GetLocation().Add(direction.Up).GetY() <= _area.GetGridSize())
		{
			int dis = abs(_snake[0].GetLocation().Add(direction.Up).GetX() - _food.GetX()) + abs(_snake[0].GetLocation().Add(direction.Up).GetY() - _food.GetY());
			if(distance <= dis)
			{
				distance = dis;
				_move = direction.Up;
			}
		}
		else
		{
			notUp = true;
			distance = 0;
		}

		if(!_snake[0].GetLocation().Add(direction.Down).Equals(part.GetLocation()) && !notDown &&
			_snake[0].GetLocation().Add(direction.Down).GetY() > 0)
		{
			int dis = abs(_snake[0].GetLocation().Add(direction.Down).GetX() - _food.GetX()) + abs(_snake[0].GetLocation().Add(direction.Down).GetY() - _food.GetY());
			if(distance <= dis)
			{
				distance = dis;
				_move = direction.Down;
			}
		}
		else
		{
			notDown = true;
			distance = 0;
		}

		if(!_snake[0].GetLocation().Add(direction.Right).Equals(part.GetLocation()) && !notRight &&
			_snake[0].GetLocation().Add(direction.Right).GetX() <= _area.GetGridSize())
		{
			int dis = abs(_snake[0].GetLocation().Add(direction.Right).GetX() - _food.GetX()) + abs(_snake[0].GetLocation().Add(direction.Right).GetY() - _food.GetY());
			if(distance <= dis)
			{
				distance = dis;
				_move = direction.Right;
			}
		}
		else
		{
			notRight = true;
			distance = 0;
		}

		if(!_snake[0].GetLocation().Add(direction.Left).Equals(part.GetLocation()) && !notLeft &&
			_snake[0].GetLocation().Add(direction.Left).GetX() > 0)
		{
			int dis = abs(_snake[0].GetLocation().Add(direction.Left).GetX() - _food.GetX()) + abs(_snake[0].GetLocation().Add(direction.Left).GetY() - _food.GetY());
			if(distance <= dis)
			{
				distance = dis;
				_move = direction.Left;
			}
		}
		else
		{
			notLeft = true;
			distance = 0;
		}
	}
}
