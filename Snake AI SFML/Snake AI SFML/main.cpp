#include "GameManager.h"

#include "SFML/System/Clock.hpp"

int main()
{
	GameManager game;
	sf::Clock clock;
	while(game.IsWindowOpen())
	{
		game.Update(clock.restart());
	}
	//TODO Delete all timers except in main.cpp

	return 0;
}