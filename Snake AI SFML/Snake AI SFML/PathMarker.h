#pragma once

#include "GridLocation.h"
#include "GameArea.h"
#include "SFML/Graphics.hpp"

class PathMarker
{
public:
	PathMarker(GridLocation _location);
	PathMarker(GridLocation _location, GameArea& _area);
	PathMarker(GridLocation _location, float _g, float _h, float _f, GridLocation _parent);
	~PathMarker() {};

	bool Equals(PathMarker& _pathmarker) { return location.Equals(_pathmarker.GetLocation()); }
	void Update(float _g, float _h, float _f, GridLocation _parent);

	bool operator==(GridLocation _other) { return location == _other; }
	bool operator==(PathMarker _other) { return location == _other.GetLocation(); }

	GridLocation GetLocation() { return location; }
	float GetG() { return G; }
	float GetF() { return F; }
	GridLocation GetParent() { return parent; }
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
	GridLocation parent;
	sf::RectangleShape marker;
};

