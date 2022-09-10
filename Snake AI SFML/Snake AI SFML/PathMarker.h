#pragma once

#include "GridLocation.h"
#include "GameArea.h"
#include "SFML/Graphics.hpp"

class PathMarker
{
public:
	PathMarker(GridLocation _direction, GridLocation _location, GameArea& _area);
	PathMarker(GridLocation _location, float _g, float _h, float _f, PathMarker* _parent);
	~PathMarker();

	bool Equals(PathMarker& _pathmarker) { return location.Equals(_pathmarker.location); }
	void Update(float _g, float _h, float _f, PathMarker* _parent);

	GridLocation GetLocation() { return location; }
	float GetG() { return G; }
	float GetF() { return F; }
	PathMarker* GetParent() { return parent; }
	sf::RectangleShape GetMarker() { return marker; }

private:
	// Calculates where to set the position to based on the origo position
	void SetPositionByOrigo(sf::Vector2f _origoPosition);
	// Calculates where to set the position based on the grid location
	void SetPositionByGridLocation(GridLocation _location, GameArea& _area);
	void SetMarker(GridLocation _location, GameArea& _area);

	GridLocation location;
	float G;
	float H;
	float F;
	PathMarker* parent;
	sf::RectangleShape marker;
};

