#include "SnakeFood.h"

int const SnakeFood::getX()
{
	return foodX;
}

int const SnakeFood::getY()
{
	return foodY;
}

//������ �������
void SnakeFood::setX(int const _x)
{
	foodX = _x;
	foodX = (foodX - (foodX % 10));
}

//������ �������
void SnakeFood::setY(int const _y)
{
	foodY = _y;
	foodY = (foodY - (foodY % 10));
}
