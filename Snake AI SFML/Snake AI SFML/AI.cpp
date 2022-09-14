#include "AI.h"
#include "AStar.h"

AI::AI() :
	moves(),
	snakeClone()
{
}

GridLocation AI::GetNextMove(std::vector<SnakePart> _snake, GridLocation _food, GameArea& _area)
{
	GridLocation move;
	if(moves.size() == 0)
	{
		snakeClone.clear();
		snakeClone.push_back(_snake);

		// Find the shortest path
		AStar aStarFood(_snake[0].GetLocation(), _food, _area, snakeClone);
		moves = aStarFood.GetMoves();

		if(!aStarFood.HasFoundPath())
		{
			// Find the shortest path
			AStar aStarTail(snakeClone[snakeClone.size() - 1][0].GetLocation(), snakeClone[snakeClone.size() - 1][snakeClone.size() - 1].GetLocation(), _area, snakeClone); // Find the longest path

			// Find the longest path
			moves = aStarTail.GetMoves();
			ExtendPath();
		}

		if(moves.size() == 0)
		{
			// Find the shortest path
			AStar aStarTail(_snake[0].GetLocation(), _snake[_snake.size() - 1].GetLocation(), _area, snakeClone);

			// Find the longest path
			moves = aStarTail.GetMoves();
			ExtendPath();
		}

		/*
		1. Compute the shortest path P1 from snake S1's head to the food. If P1 exists, go to step 2. Otherwise, go to step 4.
		2. Move a virtual snake S2 (the same as S1) to eat the food along path P1.
		3. Compute the longest path P2 from snake S2's head to its tail. If P2 exists, let D be the first direction in path P1. Otherwise, go to step 4.
		4. Compute the longest path P3 from snake S1's head to its tail. If P3 exists, let D be the first direction in path P3. Otherwise, go to step 5.
		5. Let D be the direction that makes the snake the farthest from the food.
		*/

	}

	if(moves.size() != 0)
	{
		move = _snake[0].GetLocation().GetDirectionTo(moves[moves.size() - 1].GetLocation());
		moves.erase(moves.end() - 1);
	}

	return move;
}

void AI::ExtendPath()
{
}
