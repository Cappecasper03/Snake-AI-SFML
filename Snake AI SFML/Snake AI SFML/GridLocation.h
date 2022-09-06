#pragma once

class GridLocation
{
public:
	GridLocation(int _x = 0, int _y = 0);

	int GetX() { return x; }
	int GetY() { return y; }
	void SetLocation(GridLocation _location) { x = _location.x; y = _location.y; }
	void MoveLocation(GridLocation _direction) { x += _direction.x; y += _direction.y; }

private:
	int x; // X coordinate
	int y; // Y coordinate
};

