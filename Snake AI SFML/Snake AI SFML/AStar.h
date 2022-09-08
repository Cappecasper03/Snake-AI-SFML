#pragma once

#include <vector>

#include "PathMarker.h"
#include "GameArea.h"

class AStar
{
public:
	AStar(GridLocation _startNode, GridLocation _goalNode);
	~AStar();

private:
	void Search(PathMarker* _playerNode, GameArea _area);
	bool UpdateMarker(GridLocation _position, float _g, float _h, float _f, PathMarker* _parent);
	bool IsClosed(GridLocation _location);
	void GetPath();

	std::vector<PathMarker> open; // Stores the pathmarkers that hasn't been closed
	std::vector<PathMarker> closed; // Stores all the closed pathmarkers

	// Stores the predefined values for all directions
	const GridLocation directions[4] = {GridLocation(0, 1), GridLocation(0, -1), GridLocation(1, 0), GridLocation(-1, 0)};

	PathMarker startNode;
	PathMarker goalNode;
	PathMarker lastPos;
	bool stillSearching;
};

