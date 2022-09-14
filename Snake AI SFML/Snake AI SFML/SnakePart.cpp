#include "SnakePart.h"

SnakePart::SnakePart(GridLocation _location, GameArea& _area, float _percentOfTile) :
	location(_location)
{
	visual.setFillColor(sf::Color::Green);
	visual.setSize(sf::Vector2f(_area.GetTileSize() * _percentOfTile, _area.GetTileSize() * _percentOfTile));

	SetPositionByGridLocation(_area);
}

void SnakePart::Move(GridLocation _locationOrDir, GameArea& _area)
{
	if(_locationOrDir.GetX() != 0 && _locationOrDir.GetY() != 0)
		location.SetLocation(_locationOrDir);
	else
		location.MoveLocation(_locationOrDir);

	SetPositionByGridLocation(_area);
}

void SnakePart::SetPositionByOrigo(sf::Vector2f _origoPosition)
{
	visual.setPosition(sf::Vector2f(_origoPosition.x - (visual.getSize().x / 2), _origoPosition.y - (visual.getSize().y / 2)));
}

void SnakePart::SetPositionByGridLocation(GameArea& _area)
{
	float x = _area.GetWalls().getPosition().x + _area.GetTileSize() * location.GetX() - _area.GetTileSize() / 2;
	float y = _area.GetGridLines()[0].getSize().y - (_area.GetWalls().getPosition().y + _area.GetTileSize() * location.GetY() - _area.GetTileSize() / 2);
	SetPositionByOrigo(sf::Vector2f(x, y));
}