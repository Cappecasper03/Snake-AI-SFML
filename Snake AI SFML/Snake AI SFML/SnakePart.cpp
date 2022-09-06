#include "SnakePart.h"

SnakePart::SnakePart(GridLocation _location, GameArea _area) :
	location(_location)
{
	visual.setFillColor(sf::Color::Green);
	visual.setSize(sf::Vector2f(_area.GetTileSize() * 0.75f, _area.GetTileSize() * 0.75f));

	SetPositionByGridLocation(visual, location, _area);
}

void SnakePart::SetPositionByOrigo(sf::RectangleShape& _rectangleShape, sf::Vector2f _origoPosition)
{
	_rectangleShape.setPosition(sf::Vector2f(_origoPosition.x - (_rectangleShape.getSize().x / 2), _origoPosition.y - (_rectangleShape.getSize().y / 2)));
}

void SnakePart::SetPositionByGridLocation(sf::RectangleShape& _rectangleShape, GridLocation _location, GameArea _area)
{
	float x = _area.GetWalls().getPosition().x + _area.GetTileSize() * _location.GetX() - _area.GetTileSize() / 2;
	float y = _area.GetGridLines()[0].getSize().y - (_area.GetWalls().getPosition().y + _area.GetTileSize() * _location.GetY() - _area.GetTileSize() / 2);
	SetPositionByOrigo(_rectangleShape, sf::Vector2f(x, y));
}