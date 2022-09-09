#pragma once

#include <vector>

#include "SnakePart.h"
#include "GridLocation.h"
#include "GameArea.h"

class AI
{
public:
	AI();
	~AI();

	GridLocation GetNextMove(std::vector<SnakePart> _snake, GridLocation _food, GameArea& _area);
	void ClearMoves() { moves.clear(); }

private:
	std::vector<std::vector<SnakePart>> snakeClone;
	std::vector<GridLocation> moves;
};

