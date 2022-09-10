#include "AI.h"
#include "AStar.h"

AI::AI() :
	moves(),
	snakeClone()
{
}

AI::~AI()
{
}

GridLocation AI::GetNextMove(std::vector<SnakePart> _snake, GridLocation _food, GameArea& _area)
{
	GridLocation move;
	if(moves.size() == 0)
	{
		snakeClone.clear();
		snakeClone.push_back(_snake);

		AStar aStar(snakeClone[0][0].GetLocation(), _food, _area, snakeClone);

		moves = aStar.GetMoves();
	}

	move = moves[moves.size() - 1].GetLocation(); // GetLocation in this case is GetDirection
	moves.erase(moves.end() - 1);

	return move;
}
