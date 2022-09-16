#pragma once

#include <vector>

#include "SnakePart.h"
#include "GridLocation.h"
#include "GameArea.h"
#include "PathMarker.h"

class AI
{
public:
	AI();
	~AI() {};

	GridLocation GetNextMove(std::vector<SnakePart> _snake, GridLocation _food, GameArea& _area);
	void ClearMoves() { moves.clear(); }
	std::vector<PathMarker>& GetPath() { return moves; }

private:
	void DefaultMove(GridLocation& _move, std::vector<SnakePart>& _snake, GridLocation& _food, GameArea& _area);

	std::vector<std::vector<SnakePart>> snakeClone;
	std::vector<PathMarker> moves;
};

