#pragma once

#include <vector>

#include "PathMarker.h"
#include "GameArea.h"
#include "SnakePart.h"
#include "GridLocation.h"

struct Directions // Stores the predefined values for all directions
{
	const GridLocation Up = GridLocation(0, 1);
	const GridLocation Down = GridLocation(0, -1);
	const GridLocation Right = GridLocation(1, 0);
	const GridLocation Left = GridLocation(-1, 0);
};

class AStar
{
public:
	AStar(GridLocation _startNode, GridLocation _goalNode, GameArea& _area, std::vector<std::vector<SnakePart>>& _snakeClones);
	~AStar();

	std::vector<GridLocation>& GetMoves() { return moves; };

private:
	void Search(PathMarker& _playerNode, GameArea& _area, std::vector<std::vector<SnakePart>>& _snakeClones);
	bool UpdateMarker(GridLocation _position, float _g, float _h, float _f, PathMarker* _parent);
	bool IsClosed(GridLocation _location);
	void GetPath(PathMarker* _lastPos);
	void MoveSnakeClone(GridLocation _moveDirection, GameArea& _area, std::vector<SnakePart>& _snakeClone);

	std::vector<PathMarker> open; // Stores the pathmarkers that hasn't been closed
	std::vector<PathMarker> closed; // Stores all the closed pathmarkers

	// Stores the predefined values for all directions
	Directions dir;
	const GridLocation directions[4] = {dir.Up, dir.Down, dir.Right, dir.Left};

	PathMarker startNode;
	PathMarker goalNode;
	PathMarker lastPos;
	bool stillSearching;

	std::vector<GridLocation> moves;
};

