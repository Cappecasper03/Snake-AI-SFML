#include "GameManager.h"

int main()
{
	GameManager game;

	while(game.GetState() == GameStates::Playing)
	{
		game.Update();
	}

	return 0;
}