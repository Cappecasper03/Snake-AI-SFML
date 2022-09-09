#include "GameManager.h"

#include <chrono>

int main()
{
	GameManager game;
	double deltaTime = 0;
	std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
	while(game.IsWindowOpen())
	{
		begin = std::chrono::steady_clock::now();
		game.Update(deltaTime);
		std::chrono::steady_clock::time_point stop = std::chrono::steady_clock::now();
		deltaTime = (double)std::chrono::duration_cast<std::chrono::nanoseconds>(stop - begin).count() / 1000000000;
	}

	return 0;
}