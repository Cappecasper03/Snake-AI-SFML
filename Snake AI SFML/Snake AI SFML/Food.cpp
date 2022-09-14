#include "Food.h"
#include "SnakePart.h"

#include <random>
#include <vector>

Food::Food(GameArea& _area)
{
	visual.setFillColor(sf::Color::Red);
	visual.setSize(sf::Vector2f(_area.GetTileSize() * 0.5f, _area.GetTileSize() * 0.5f));

	RandomizeLocation(_area);
}

void Food::RandomizeLocation(GameArea& _area)
{
	std::srand((unsigned int)std::time(0));
	do
	{
		location.SetLocation(GridLocation(1 + (std::rand() % _area.GetGridSize()), 1 + (std::rand() % _area.GetGridSize())));
	} while(location.GetX() == _area.GetGridSize() / 2 && location.GetY() == _area.GetGridSize() / 2);

	SetPositionByGridLocation(_area);
}

void Food::RandomizeLocation(GameArea& _area, std::vector<SnakePart> _snake)
{
	std::srand((unsigned int)std::time(0));
	bool onSnake = false;
	do
	{
		onSnake = false;
		location.SetLocation(GridLocation(1 + (std::rand() % _area.GetGridSize()), 1 + (std::rand() % _area.GetGridSize())));

		for(SnakePart snakePart : _snake)
		{
			if(location.Equals(snakePart.GetLocation()))
			{
				onSnake = true;
				break;
			}
		}
	} while(onSnake);

	SetPositionByGridLocation(_area);
}

void Food::SetPositionByOrigo(sf::Vector2f _origoPosition)
{
	visual.setPosition(sf::Vector2f(_origoPosition.x - (visual.getSize().x / 2), _origoPosition.y - (visual.getSize().y / 2)));
}

void Food::SetPositionByGridLocation(GameArea& _area)
{
	float x = _area.GetWalls().getPosition().x + _area.GetTileSize() * location.GetX() - _area.GetTileSize() / 2;
	float y = _area.GetGridLines()[0].getSize().y - (_area.GetWalls().getPosition().y + _area.GetTileSize() * location.GetY() - _area.GetTileSize() / 2);
	SetPositionByOrigo(sf::Vector2f(x, y));
}