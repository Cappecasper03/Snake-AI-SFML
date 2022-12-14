#include "GameManager.h"
#include <iostream>

GameManager::GameManager() :
	window(sf::VideoMode(1200, 800), "Snake AI"),
	area(20, (float)window.getSize().y, window.getSize().x),
	FixedUpdateTimer(0),
	FixedUpdateTime(.05f),
	state(GameStates::Playing),
	moveDirection(),
	food(area),
	snake(SnakePart(GridLocation(area.GetGridSize() / 2, area.GetGridSize() / 2), area, .7f))
{
	snake.Grow(area);
}

void GameManager::Update(sf::Time _deltaTime)
{
	FixedUpdateTimer += _deltaTime.asSeconds();

	if(state == GameStates::Playing)
	{
		if(FixedUpdateTimer >= FixedUpdateTime) // Only updates on fixed intervals
		{
			FixedUpdateTimer = 0;

			sf::Clock clock;
			moveDirection = player.GetNextMove(snake, food.GetLocation(), area);
			sf::Time time = clock.restart();
			if(time.asMilliseconds() > 0)
				std::cout << time.asMilliseconds() << "\n\n";

			snake.Move(moveDirection, area);
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

void GameManager::CheckCollision()
{
	// If the snake head is on the food
	if(snake.GetHead().GetLocation().Equals(food.GetLocation()))
	{
		snake.Grow(area);
		food.RandomizeLocation(area, snake.GetSnake());

		if((int)snake.GetSnake().size() == area.GetGridSize() * area.GetGridSize())
		{
			GridLocation dir = snake.GetHead().GetLocation().GetDirectionTo(food.GetLocation());
			snake.Move(dir, area);
			state = GameStates::Won;
		}
	}

	// If the snake head is outside the border walls
	if(snake.GetHead().GetLocation().GetX() <= 0 || snake.GetHead().GetLocation().GetX() > area.GetGridSize() ||
		snake.GetHead().GetLocation().GetY() <= 0 || snake.GetHead().GetLocation().GetY() > area.GetGridSize())
	{
		state = GameStates::Lost;
	}
	else
	{
		for(int i = 2; i < snake.GetSnake().size(); i++) // i = 2 because the head can't be on the first body part or itself
		{
			// If the snake head is on it's body
			if(snake.GetHead().GetLocation().Equals(snake.GetSnake()[i].GetLocation()))
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

	bool drawPath = true;
	if(drawPath)
	{
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
				line[1].position = snake.GetHead().GetVisual().getPosition() + snake.GetHead().GetVisual().getSize() / 2.f;
			}
			window.draw(line, 2, sf::Lines);
			window.draw(marker);
		}
	}

	window.draw(food.GetVisual());

	line[0].color = sf::Color::Green;
	line[1].color = sf::Color::Green;
	for(int i = 0; i < snake.GetSnake().size(); i++)
	{
		sf::RectangleShape visual = snake.GetSnake()[i].GetVisual();
		if(i < snake.GetSnake().size() - 1)
		{
			sf::RectangleShape visual2 = snake.GetSnake()[i + 1].GetVisual();

			line[0].position = visual.getPosition() + visual.getSize() / 2.f;
			line[1].position = visual2.getPosition() + visual2.getSize() / 2.f;
			window.draw(line, 2, sf::Lines);
		}

		window.draw(visual);
	}

	window.display();
}