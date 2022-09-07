#pragma once

#include "GridLocation.h"
#include "GameArea.h"

class Food
{
public:
	Food(GameArea _area);

	// Calculates where to set the position to based on the origo position
	void SetPositionByOrigo(sf::RectangleShape& _rectangleShape, sf::Vector2f _origoPosition);
	// Calculates where to set the position based on the grid location
	void SetPositionByGridLocation(sf::RectangleShape& _rectangleShape, GridLocation _location, GameArea _area);

	void RandomizeLocation(GameArea _area);

private:
	GridLocation location; // Coordinates of the food
	sf::RectangleShape visual; // Stores the visual of the food
};

