#pragma once

#include <vector>

#include "Snake.h"
#include "SnakePart.h"
#include "GridLocation.h"
#include "GameArea.h"
#include "PathMarker.h"

class AI
{
public:
	AI();
	~AI() {};

	GridLocation GetNextMove(Snake _snake, GridLocation _food, GameArea& _area);
	void ClearMoves() { moves.clear(); }
	std::vector<PathMarker>& GetPath() { return moves; }

private:
	void DefaultMove(GridLocation& _move, std::vector<SnakePart>& _snake, GridLocation& _food, GameArea& _area);

	std::vector<Snake> snakeClone;
	std::vector<PathMarker> moves;

	bool foundFastPath;
};

