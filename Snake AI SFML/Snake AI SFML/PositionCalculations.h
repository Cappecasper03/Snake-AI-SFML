#pragma once

#include "SFML/Graphics.hpp"
#include "GridLocation.h"
#include "GameArea.h"

class PositionCalculations
{
protected:
	// Calculates where to set the position to based on the origo position
	void SetPositionByOrigo(sf::RectangleShape& _rectangleShape, sf::Vector2f _origoPosition);

	// Calculates where to set the position based on the grid location
	void SetPositionByGridLocation(sf::RectangleShape& _rectangleShape, GridLocation _location, GameArea _area);
};

