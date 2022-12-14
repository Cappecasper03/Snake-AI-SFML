#pragma once

#include <vector>

#include "SFML/Graphics.hpp"
#include "GridLocation.h"
#include "GameArea.h"
#include "PathMarker.h"

class SnakePart
{
public:
	SnakePart(GridLocation _location);
	SnakePart(GridLocation _location, GameArea& _area, float _percentOfTile);
	~SnakePart() {};

	void Move(GridLocation _locationOrDir, GameArea& _area);

	bool operator==(GridLocation _other) { return location == _other; }
	bool operator==(SnakePart _other) { return location == _other.location; }

	GridLocation GetLocation() { return location; }
	sf::RectangleShape& GetVisual() { return visual; }

private:
	// Calculates where to set the position to based on the origo position
	void SetPositionByOrigo(sf::Vector2f _origoPosition);
	// Calculates where to set the position based on the grid location
	void SetPositionByGridLocation(GameArea& _area);

	GridLocation location; // Coordinates of the snake part
	sf::RectangleShape visual; // Stores the visual of the snake body/head
};
