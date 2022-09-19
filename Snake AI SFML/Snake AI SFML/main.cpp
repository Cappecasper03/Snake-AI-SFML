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

	return 0;
}