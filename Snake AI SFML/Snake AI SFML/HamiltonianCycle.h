#pragma once

#include <vector>

#include "PathMarker.h"
#include "Snake.h"
#include "SnakePart.h"
#include "GameArea.h"

struct Node
{
	GridLocation location;
	bool isVisited = false;
};

class HamiltonianCycle // Or longest path
{
public:
	HamiltonianCycle();
	~HamiltonianCycle() {};

	void GetMoves(Snake _snake, GameArea& _area, std::vector<Snake>& _snakeClones, std::vector<PathMarker>& _moves);

private:
	void ExtendPath(std::vector<PathMarker>& _moves, Snake& _snakeClone, GameArea& _area);
	void IsVisited(Node& _cUpRight, Node& _nUpRight, Node& _cDownLeft, Node& _nDownLeft, std::vector<PathMarker>& _movesCopy);
	void IsOnSnake(Node& _cUpRight, Node& _nUpRight, Node& _cDownLeft, Node& _nDownLeft, Snake& _snakeClone);
	void IsOutsideGameArea(Node& _cUpRight, Node& _nUpRight, Node& _cDownLeft, Node& _nDownLeft, GameArea& _area);
};

