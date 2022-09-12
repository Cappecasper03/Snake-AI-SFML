#include "GameManager.h"

#include <chrono>
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