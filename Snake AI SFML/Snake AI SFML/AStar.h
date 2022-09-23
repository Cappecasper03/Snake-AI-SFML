#pragma once

#include <vector>

#include "PathMarker.h"
#include "GameArea.h"
#include "Snake.h"
#include "SnakePart.h"
#include "GridLocation.h"

struct Directions // Stores the predefined values for all directions
{
	const GridLocation Up = GridLocation(0, 1);
	const GridLocation Down = GridLocation(0, -1);
	const GridLocation Right = GridLocation(1, 0);
	const GridLocation Left = GridLocation(-1, 0);
};

class AStar // Or shortest path
{
public:
	AStar(GridLocation _startNode, GridLocation _goalNode, GameArea& _area, std::vector<Snake>& _snakeClones);
	~AStar() {};

	std::vector<PathMarker>& GetMoves() { return moves; };
	bool HasFoundPath() { return foundPath; }

private:
	void Search(PathMarker& _playerNode, GameArea& _area, std::vector<Snake>& _snakeClones);
	bool UpdateMarker(GridLocation _position, float _g, float _h, float _f, GridLocation _parent);
	bool IsClosed(GridLocation _location);
	void GetPath(GridLocation _lastPos, GameArea& _area);
	void MoveSnakeClone(GridLocation _moveDirection, GameArea& _area, Snake& _snakeClone);

	void shortPath(GameArea& _area, std::vector<Snake>& _snakeClones);

	std::vector<PathMarker> open; // Stores the pathmarkers that hasn't been visited
	std::vector<PathMarker> closed; // Stores all the visited pathmarkers

	// Stores the predefined values for all directions
	Directions dir;
	const GridLocation directions[4] = {dir.Up, dir.Down, dir.Right, dir.Left};

	PathMarker startNode;
	PathMarker goalNode;
	PathMarker lastPos;
	bool stillSearching;
	bool foundPath;

	std::vector<PathMarker> moves;
};

