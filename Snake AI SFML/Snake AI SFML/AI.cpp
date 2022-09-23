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

GridLocation AI::GetNextMove(Snake _snake, GridLocation _food, GameArea& _area)
{
	std::vector<PathMarker> movesCopy;
	GridLocation move;
	snakeClone.clear();
	snakeClone.push_back(_snake);


	if(!foundFastPath)
	{
		// Find the longest path to tail
		std::vector<Snake> sSnakeClone;
		sSnakeClone.push_back(_snake);
		std::vector<PathMarker> tMovesCopy;
		HamiltonianCycle hamiltonianCycle;
		std::thread hamiltonianCycleThread(&HamiltonianCycle::GetMoves, hamiltonianCycle, _snake, std::ref(_area), std::ref(sSnakeClone), std::ref(tMovesCopy));

		// Find the shortest path to food unless the snake fills up 50% of the area
		if(_snake.GetSnake().size() <= _area.GetGridSize() * _area.GetGridSize() * .5f)
		{
			AStar aStarFood(_snake.GetHead().GetLocation(), _food, _area, snakeClone);
			movesCopy = aStarFood.GetMoves();

			if(aStarFood.HasFoundPath() && _snake.GetSnake().size() >= 3)
			{
				Snake snakeCloneClone(snakeClone[0]);
				snakeCloneClone.GetSnake().push_back(snakeCloneClone.GetTail()); // Add 1 part because it has "eaten" the food

				snakeClone.clear();
				snakeClone.push_back(snakeCloneClone);

				// Check if longest path to tail exist
				std::vector<PathMarker> tempMoves;
				HamiltonianCycle hamiltonianCycleT;
				hamiltonianCycleT.GetMoves(snakeCloneClone, _area, snakeClone, tempMoves);
				if(tempMoves.size() == 0)
					movesCopy.clear();
				else
					foundFastPath = true;
			}
			else if(aStarFood.HasFoundPath() && _snake.GetSnake().size() < 3)
				foundFastPath = true;
		}

		if(hamiltonianCycleThread.joinable())
			hamiltonianCycleThread.join();

		if(!foundFastPath)
			movesCopy = tMovesCopy;


		// Choose a safe default move
		if(!foundFastPath && movesCopy.size() == 0)
			DefaultMove(move, _snake.GetSnake(), _food, _area);

		moves = movesCopy;
	}

	if(moves.size() != 0)
	{
		move = _snake.GetHead().GetLocation().GetDirectionTo(moves[moves.size() - 1].GetLocation());
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
