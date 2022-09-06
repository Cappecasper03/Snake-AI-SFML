#include "SnakePart.h"

SnakePart::SnakePart(GridLocation _location, GameArea _area) :
	location(_location)
{
	visual.setFillColor(sf::Color::Green);
	visual.setSize(sf::Vector2f(_area.GetTileSize() * 0.75f, _area.GetTileSize() * 0.75f));

	/*SetPositionByGridLocation(visual, location, _area);
	float x = _area.GetWalls().getPosition().x + (_area.GetTileSize() * _location.GetX()) - _area.GetTileSize() / 2;
	float y = _area.GetGridSize() - _area.GetWalls().getPosition().y + (_area.GetTileSize() * _location.GetY()) - _area.GetTileSize() / 2;

	_rectangleShape.setPosition(sf::Vector2f(_origoPosition.x - (_rectangleShape.getSize().x / 2), _origoPosition.y - (_rectangleShape.getSize().y / 2)));*/
}