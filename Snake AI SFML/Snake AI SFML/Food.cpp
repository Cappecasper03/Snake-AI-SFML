#include "Food.h"

#include <random>

Food::Food(GameArea _area)
{
	visual.setFillColor(sf::Color::Red);
	visual.setSize(sf::Vector2f(_area.GetTileSize() * 0.5f, _area.GetTileSize() * 0.5f));

	RandomizeLocation(_area);
}

void Food::SetPositionByOrigo(sf::RectangleShape& _rectangleShape, sf::Vector2f _origoPosition)
{
	_rectangleShape.setPosition(sf::Vector2f(_origoPosition.x - (_rectangleShape.getSize().x / 2), _origoPosition.y - (_rectangleShape.getSize().y / 2)));
}

void Food::SetPositionByGridLocation(sf::RectangleShape& _rectangleShape, GridLocation _location, GameArea _area)
{
	float x = _area.GetWalls().getPosition().x + _area.GetTileSize() * _location.GetX() - _area.GetTileSize() / 2;
	float y = _area.GetGridLines()[0].getSize().y - (_area.GetWalls().getPosition().y + _area.GetTileSize() * _location.GetY() - _area.GetTileSize() / 2);
	SetPositionByOrigo(_rectangleShape, sf::Vector2f(x, y));
}

void Food::RandomizeLocation(GameArea _area)
{
	//Todo Implement check for snake
	std::srand(std::time(0));
	location.SetLocation(GridLocation(1 + (std::rand() % _area.GetGridSize()), 1 + (std::rand() % _area.GetGridSize())));

	SetPositionByGridLocation(visual, location, _area);
}