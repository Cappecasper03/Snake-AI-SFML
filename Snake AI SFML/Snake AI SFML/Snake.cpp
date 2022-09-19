#include "Snake.h"

Snake::Snake(SnakePart _head) :
	snake()
{
	snake.push_back(_head);
}

void Snake::Move(GridLocation& _moveDirection, GameArea& _area)
{
	for(size_t i = (int)snake.size() - 1; i > 0; i--)
	{
		snake[i].Move(snake[i - 1].GetLocation(), _area);
	}
	snake[0].Move(_moveDirection, _area);
}