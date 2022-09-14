#pragma once

#include "GridLocation.h"
#include "GameArea.h"
#include "SnakePart.h"

#include <vector>


class Food
{
public:
	Food(GameArea& _area);
	~Food() {};

	// Randomizes a location in the game area
	void RandomizeLocation(GameArea& _area);
	void RandomizeLocation(GameArea& _area, std::vector<SnakePart> _snake);

	GridLocation GetLocation() { return location; }
	sf::RectangleShape& GetVisual() { return visual; }

private:
	// Calculates where to set the position to based on the origo position
	void SetPositionByOrigo(sf::Vector2f _origoPosition);
	// Calculates where to set the position based on the grid location
	void SetPositionByGridLocation(GameArea& _area);

	GridLocation location; // Coordinates of the food
	sf::RectangleShape visual; // Stores the visual of the food
};

