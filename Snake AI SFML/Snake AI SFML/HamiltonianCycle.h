#pragma once

#include <vector>

#include "PathMarker.h"
#include "SnakePart.h"
#include "GameArea.h"

class HamiltonianCycle
{
public:
	HamiltonianCycle(std::vector<SnakePart> _snake, GameArea& _area, std::vector<std::vector<SnakePart>>& _snakeClones);
	~HamiltonianCycle() {};

	std::vector<PathMarker>& GetMoves() { return moves; };

private:
	void ExtendPath(std::vector<PathMarker>& _moves, std::vector<SnakePart>& _snakeClone, GameArea& _area);

	std::vector<PathMarker> moves;
};

