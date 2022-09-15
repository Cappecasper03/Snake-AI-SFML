#include "AI.h"
#include "AStar.h"
#include "HamiltonianCycle.h"

#include <math.h>

AI::AI() :
	moves(),
	snakeClone()
{
}

GridLocation AI::GetNextMove(std::vector<SnakePart> _snake, GridLocation _food, GameArea& _area)
{
	GridLocation move;
	snakeClone.clear();
	snakeClone.push_back(_snake);

	// Find the shortest path to food
	AStar aStarFood(_snake[0].GetLocation(), _food, _area, snakeClone);
	std::vector<PathMarker> movesCopy = aStarFood.GetMoves();

	if(aStarFood.HasFoundPath())
	{
		std::vector<SnakePart> snakeCloneClone(snakeClone[0]);

		// Find the longest path to tail
		HamiltonianCycle hamiltonianCycle(snakeCloneClone, _area, snakeClone);
		if(hamiltonianCycle.GetMoves().size() == 0)
			movesCopy.clear();
		else
			moves = movesCopy;
	}

	if(moves.size() == 0)
	{
		if(movesCopy.size() == 0)
		{
			snakeClone.clear();
			snakeClone.push_back(_snake);

			// Find the longest path to tail
			HamiltonianCycle hamiltonianCycle(_snake, _area, snakeClone);
			movesCopy = hamiltonianCycle.GetMoves();
		}

		if(movesCopy.size() == 0)
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
					if(distance < dis)
					{
						distance = dis;
						move = direction.Up;
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
					if(distance < dis)
					{
						distance = dis;
						move = direction.Down;
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
					if(distance < dis)
					{
						distance = dis;
						move = direction.Right;
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
					if(distance < dis)
					{
						distance = dis;
						move = direction.Left;
					}
				}
				else
				{
					notLeft = true;
					distance = 0;
				}
			}
		}

		moves = movesCopy;
	}

	if(moves.size() != 0)
	{
		move = _snake[0].GetLocation().GetDirectionTo(moves[moves.size() - 1].GetLocation());
		moves.erase(moves.end() - 1);
	}

	return move;
}