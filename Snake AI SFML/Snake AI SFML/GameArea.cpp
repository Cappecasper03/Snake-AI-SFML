#include "GameArea.h"

GameArea::GameArea(int _gridSize, float _height, int _width)
{
	gridSize = _gridSize;

	float outlineThickness = 10;
	tileSize = (_height - outlineThickness * 2) / gridSize;
	walls.setSize(sf::Vector2f(_height - outlineThickness * 2, _height - outlineThickness * 2));
	walls.setFillColor(sf::Color::Transparent);
	walls.setOutlineColor(sf::Color::Blue);
	walls.setOutlineThickness(outlineThickness);
	/*SetPositionByOrigo(walls, sf::Vector2f(_width / 2.f, _height / 2.f));
	_rectangleShape.setPosition(sf::Vector2f(_origoPosition.x - (_rectangleShape.getSize().x / 2), _origoPosition.y - (_rectangleShape.getSize().y / 2)));*/

	outlineThickness /= 4;
	for(int i = 0; i < gridSize - 1; i++)
	{
		sf::RectangleShape line;
		line.setFillColor(sf::Color::Blue);
		line.setSize(sf::Vector2f(outlineThickness, _height));
		/*SetPositionByOrigo(line, sf::Vector2f(walls.getPosition().x + (tileSize * (i + 1)), _height / 2.f));
		_rectangleShape.setPosition(sf::Vector2f(_origoPosition.x - (_rectangleShape.getSize().x / 2), _origoPosition.y - (_rectangleShape.getSize().y / 2)));*/
		gridLines.push_back(line);

		line.setSize(sf::Vector2f(_height, outlineThickness));
		/*SetPositionByOrigo(line, sf::Vector2f(_width / 2.f, walls.getPosition().y + (tileSize * (i + 1))));
		_rectangleShape.setPosition(sf::Vector2f(_origoPosition.x - (_rectangleShape.getSize().x / 2), _origoPosition.y - (_rectangleShape.getSize().y / 2)));*/
		gridLines.push_back(line);
	}
}
