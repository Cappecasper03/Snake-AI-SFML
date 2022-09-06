#pragma once

#include <vector>

#include "SFML/Graphics.hpp"
#include "GridLocation.h"
#include "GameArea.h"

class SnakePart 
{
public:
	SnakePart(GridLocation _location, GameArea _area);

	void Move(GridLocation _direction) { location.MoveLocation(_direction); }
	sf::RectangleShape GetVisual() { return visual; }

private:
	GridLocation location; // Coordinates of the snake part
	sf::RectangleShape visual; // Stores the visual of the snake body/head
};
