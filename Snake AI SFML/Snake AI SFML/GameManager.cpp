#include "GameManager.h"

#include <thread>

GameManager::GameManager() :
	window(sf::VideoMode(1200, 800), "Snake AI"),
	area(10, (float)window.getSize().y, window.getSize().x),
	FixedUpdateTimer(0),
	FixedUpdateTime(0.2f),
	state(GameStates::Playing),
	moveDirection(),
	food(area)
{
	snake.push_back(SnakePart(GridLocation(area.GetGridSize() / 2, area.GetGridSize() / 2), area, 0.7f));
	snake.push_back(SnakePart(snake[snake.size() - 1].GetLocation(), area, 0.5f));
}

GameManager::~GameManager()
{
}

void GameManager::Update(sf::Time _deltaTime)
{
	FixedUpdateTimer += _deltaTime.asSeconds();

	if(state == GameStates::Playing)
	{
		if(FixedUpdateTimer >= FixedUpdateTime) // Only updates on fixed intervals
		{
			FixedUpdateTimer = 0;

			moveDirection = player.GetNextMove(snake, food.GetLocation(), area); //Todo Move to it's own thread
			Move();
			CheckCollision();
		}
	}

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

void GameManager::Move()
{
	for(int i = (int)snake.size() - 1; i > 0; i--)
	{
		snake[i].Move(snake[i - 1].GetLocation(), area);
	}
	snake[0].Move(moveDirection, area);
}

void GameManager::CheckCollision()
{
	// If the snake head is on the food
	if(snake[0].GetLocation().Equals(food.GetLocation()))
	{
		Grow();
		food.RandomizeLocation(area, snake);

		if(snake.size() == area.GetGridSize() * area.GetGridSize())
			state = GameStates::Won;
	}

	// If the snake head is outside the border walls
	if(snake[0].GetLocation().GetX() <= 0 || snake[0].GetLocation().GetX() > area.GetGridSize() ||
		snake[0].GetLocation().GetY() <= 0 || snake[0].GetLocation().GetY() > area.GetGridSize())
	{
		state = GameStates::Lost;
	}
	else
	{
		for(int i = 2; i < snake.size(); i++) // i = 2 because the head can't be on the first body part or itself
		{
			// If the snake head is on it's body
			if(snake[0].GetLocation().Equals(snake[i].GetLocation()))
				state = GameStates::Lost;
		}
	}
}

void GameManager::Draw()
{
	window.clear(sf::Color::Black);
	window.draw(area.GetWalls());
	for(int i = 0; i < player.GetPath().size(); i++)
	{
		window.draw(player.GetPath()[i].GetMarker());
	}
	for(int i = 0; i < area.GetGridLines().size(); i++)
	{
		window.draw(area.GetGridLines()[i]);
	}
	window.draw(food.GetVisual());
	for(SnakePart part : snake)
	{
		window.draw(part.GetVisual());
	}
	window.display();
}