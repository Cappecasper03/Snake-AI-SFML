#pragma once

#include "SnakePart.h"
#include "GridLocation.h"
#include "GameArea.h"

#include <vector>

class Snake
{
public:
	Snake(SnakePart _head);
	~Snake() {};

	void Move(GridLocation& _moveDirection, GameArea& _area);
	void Grow(GameArea& _area) { snake.push_back(SnakePart(snake[snake.size() - 1].GetLocation(), _area, .5f)); }

	bool operator==(std::vector<SnakePart> _other) { return snake[0].GetLocation() == _other[0].GetLocation(); }

	std::vector<SnakePart>& GetSnake() { return snake; }
	SnakePart& GetHead() { return snake[0]; }
	SnakePart& GetTail() { return snake[snake.size() - 1]; }

private:
	std::vector<SnakePart> snake;
};