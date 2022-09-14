#pragma once

#include "SFML/Graphics.hpp"

class GridLocation
{
public:
	GridLocation(int _x = 0, int _y = 0);
	~GridLocation() {};

	void SetLocation(GridLocation _location) { x = _location.x; y = _location.y; }
	void MoveLocation(GridLocation _direction) { x += _direction.x; y += _direction.y; }
	GridLocation Add(GridLocation _location) { return  GridLocation(x + _location.GetX(), y + _location.GetY()); }

	GridLocation GetDirectionTo(GridLocation _to) { return GridLocation(_to.GetX() - x, _to.GetY() - y); }
	sf::Vector2f ToVector() { return sf::Vector2f((float)x, (float)y); }
	bool Equals(GridLocation _location) { return _location.ToVector() == ToVector(); }

	int GetX() { return x; }
	int GetY() { return y; }

private:
	int x; // X coordinate
	int y; // Y coordinate
};

