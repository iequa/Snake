#pragma once

class SnakeFood
{
private:
	int foodX;
	int foodY;
public:
	SnakeFood() = default;
	~SnakeFood() = default;
	
	int const getX();
	int const getY();

	void setX(int _x);
	void setY(int _y);
};
