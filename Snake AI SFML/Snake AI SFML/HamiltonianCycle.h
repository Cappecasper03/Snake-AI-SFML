#pragma once

#include <vector>

#include "PathMarker.h"
#include "SnakePart.h"
#include "GameArea.h"

struct Node
{
	GridLocation location;
	bool isVisited = false;
};

class HamiltonianCycle
{
public:
	HamiltonianCycle();
	~HamiltonianCycle() {};

	void GetMoves(std::vector<SnakePart> _snake, GameArea& _area, std::vector<std::vector<SnakePart>>& _snakeClones, std::vector<PathMarker>& _moves);

private:
	void ExtendPath(std::vector<PathMarker>& _moves, std::vector<SnakePart>& _snakeClone, GameArea& _area);
	void IsVisited(Node& _cUpRight, Node& _nUpRight, Node& _cDownLeft, Node& _nDownLeft, std::vector<PathMarker>& _movesCopy);
	void IsOnSnake(Node& _cUpRight, Node& _nUpRight, Node& _cDownLeft, Node& _nDownLeft, std::vector<SnakePart>& _snakeClone);
	void IsOutsideGameArea(Node& _cUpRight, Node& _nUpRight, Node& _cDownLeft, Node& _nDownLeft, GameArea& _area);

	std::vector<PathMarker> moves;
};

