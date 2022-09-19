#include "GameManager.h"

GameManager::GameManager() :
	window(sf::VideoMode(1200, 800), "Snake AI"),
	area(10, (float)window.getSize().y, window.getSize().x),
	FixedUpdateTimer(0),
	FixedUpdateTime(.05f),
	state(GameStates::Playing),
	moveDirection(),
	food(area)
{
	snake.push_back(SnakePart(GridLocation(area.GetGridSize() / 2, area.GetGridSize() / 2), area, .7f));
	Grow();
}

void GameManager::Update(sf::Time _deltaTime)
{
	FixedUpdateTimer += _deltaTime.asSeconds();

	if(state == GameStates::Playing)
	{
		if(FixedUpdateTimer >= FixedUpdateTime) // Only updates on fixed intervals
		{
			FixedUpdateTimer = 0;

			moveDirection = player.GetNextMove(snake, food.GetLocation(), area);
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
	for(size_t i = (int)snake.size() - 1; i > 0; i--)
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

		if((int)snake.size() == area.GetGridSize() * area.GetGridSize())
		{
			Move();
			state = GameStates::Won;
		}
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
			{
				state = GameStates::Lost;
			}
		}
	}
}

void GameManager::Draw()
{
	window.clear(sf::Color::Black);
	sf::Vertex line[2];

	window.draw(area.GetWalls());
	for(int i = 0; i < area.GetGridLines().size(); i++)
	{
		window.draw(area.GetGridLines()[i]);
	}

	line[0].color = sf::Color::Magenta;
	line[1].color = sf::Color::Magenta;
	for(int i = 0; i < player.GetPath().size(); i++)
	{
		sf::RectangleShape marker = player.GetPath()[i].GetMarker();
		if(i < player.GetPath().size() - 1)
		{
			sf::RectangleShape marker2 = player.GetPath()[i + 1].GetMarker();

			line[0].position = marker.getPosition() + marker.getSize() / 2.f;
			line[1].position = marker2.getPosition() + marker2.getSize() / 2.f;
		}
		else
		{
			line[0].position = marker.getPosition() + marker.getSize() / 2.f;
			line[1].position = snake[0].GetVisual().getPosition() + snake[0].GetVisual().getSize() / 2.f;
		}
		window.draw(line, 2, sf::Lines);
		window.draw(marker);
	}

	window.draw(food.GetVisual());

	line[0].color = sf::Color::Green;
	line[1].color = sf::Color::Green;
	for(int i = 0; i < snake.size(); i++)
	{
		sf::RectangleShape visual = snake[i].GetVisual();
		if(i < snake.size() - 1)
		{
			sf::RectangleShape visual2 = snake[i + 1].GetVisual();

			line[0].position = visual.getPosition() + visual.getSize() / 2.f;
			line[1].position = visual2.getPosition() + visual2.getSize() / 2.f;
			window.draw(line, 2, sf::Lines);
		}

		window.draw(visual);
	}

	window.display();
}