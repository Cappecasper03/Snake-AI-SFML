#pragma once

#include <vector>

#include "SFML/Graphics.hpp"

class GameArea
{
public:
	GameArea(int _gridSize, float _height, int _width);
	~GameArea();

	// Calculates where to set the position to based on the origo position
	void SetPositionByOrigo(sf::RectangleShape& _rectangleShape, sf::Vector2f _origoPosition);

	int GetGridSize() { return gridSize; }
	float GetTileSize() { return tileSize; }
	sf::RectangleShape GetWalls() { return walls; }
	std::vector<sf::RectangleShape> GetGridLines() { return gridLines; }

private:
	int gridSize; // Size of every row and column
	float tileSize; // Size of every tile on the grid

	sf::RectangleShape walls; // Stores the game area outline (walls)
	std::vector<sf::RectangleShape> gridLines; // Stores the game area gridlines
};

