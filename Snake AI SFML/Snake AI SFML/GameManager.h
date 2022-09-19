#pragma once

#include "SFML/Graphics.hpp"
#include "GridLocation.h"
#include "GameArea.h"
#include "Snake.h"
#include "SnakePart.h"
#include "Food.h"
#include "AI.h"

struct Directions // Stores the predefined values for all directions
{
	const GridLocation Up = GridLocation(0, 1);
	const GridLocation Down = GridLocation(0, -1);
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
	~GameManager() {};

	void Update(sf::Time _deltaTime);
	void CheckCollision();

	bool IsWindowOpen() { return window.isOpen(); }

private:
	void Draw();

	GameStates state; // Stores the state of the game
	sf::RenderWindow window; // Controls the game window
	double FixedUpdateTimer; // Used to update with a fixed interval (time in seconds)
	float FixedUpdateTime; // Used to set the fixed update interval (time in seconds)

	GameArea area; // Stores the game area information
	AI player; // Controls the snake
	Snake snake; // Controls the snake
	GridLocation moveDirection; // Stores the current direction to move in
	Food food; // Controls the food

	Directions directions; // Stores the predefined values for all directions
};

