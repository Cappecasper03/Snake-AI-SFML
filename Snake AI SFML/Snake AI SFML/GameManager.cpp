#include "GameManager.h"

GameManager::GameManager() :
	window(sf::VideoMode(1200, 800), "Snake AI"),
	area(10, (float)window.getSize().y, window.getSize().x),
	state(GameStates::Playing),
	food()
{
	snake.push_back(SnakePart(GridLocation(area.GetGridSize() / 2, area.GetGridSize() / 2), area));
}

void GameManager::Update()
{
	sf::Event event;
	while(window.pollEvent(event))
	{
		if(event.type == sf::Event::Closed)
		{
			state = GameStates::NotPlaying;
			window.close();
		}
	}

	Draw();
}

void GameManager::Draw()
{
	window.clear(sf::Color::Black);
	window.draw(area.GetWalls());
	for(int i = 0; i < area.GetGridLines().size(); i++)
	{
		window.draw(area.GetGridLines()[i]);
	}
	for(SnakePart part : snake)
	{
		window.draw(part.GetVisual());
	}
	window.display();
}