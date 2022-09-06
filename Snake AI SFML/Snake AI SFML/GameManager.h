#pragma once

#include "SFML/Graphics.hpp"
#include "GameArea.h"
#include "SnakePart.h"
#include "Food.h"

struct Directions // Stores the predefined values for all directions
{
	const GridLocation Up = GridLocation(0, -1);
	const GridLocation Down = GridLocation(0, 1);
	const GridLocation Right = GridLocation(1, 0);
	const GridLocation Left = GridLocation(-1, 0);
};
enum GameStates
{
	Playing,
	NotPlaying,
	Won,
	Lost
};

class GameManager
{
public:
	GameManager();

	GameStates GetState() { return state; }
	void Update();

private:
	void Draw();

	GameStates state; // Stores the state of the game
	sf::RenderWindow window; // Controlls the game window

	GameArea area;
	std::vector<SnakePart> snake;
	Food food;
};

