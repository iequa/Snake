#include "Snake.h"

SNAKE::SNAKE() :posHead(new coords[1]), posTail(new coords[1]), snakeLen(1)
{
	posHead[0].x = 20;
	posHead[0].y = 100;
	posHead[0].oldX = 10;
	posHead[0].oldY = posHead[0].y-10;

	posTail[0].x = 10;
	posTail[0].y = posHead[0].y;
	posTail[0].oldX = 0;
	posTail[0].oldY = posTail[0].y-10;

}

int SNAKE::getHeadPosX(int i)
{
	return posHead[i].x;
}

int SNAKE::getHeadPosY(int i)
{
	return posHead[i].y;
}

int SNAKE::getHeadPosOldX(int i)
{
	return posHead[i].oldX;
}

int SNAKE::getHeadPosOldY(int i)
{
	return posHead[i].oldY;
}

int SNAKE::getTailPosX(int i)
{
	return posTail[i].x;
}

int SNAKE::getTailPosY(int i)
{
	return posTail[i].y;
}

int SNAKE::getTailPosOldX(int i)
{
	return posTail[i].oldX;
}

int SNAKE::getTailPosOldY(int i)
{
	return posTail[i].oldY;
}

void SNAKE::setPos(coords* _Head, coords* _Tail)
{
	for (int i = 0; i < snakeLen; i++)
	{
		posHead[i].x = _Head[i].x;
		posHead[i].y = _Head[i].y;
		posHead[i].oldX = _Head[i].oldX;
		posHead[i].oldY = _Head[i].oldY;

		posTail[i].x = _Tail[i].x;
		posTail[i].y = _Tail[i].y;
		posTail[i].oldX = _Tail[i].oldX;
		posTail[i].oldY = _Tail[i].oldY;
	}
}

void SNAKE::moveLeft()
{
	for (int i = 0; i < snakeLen-1; i++)
	{
		posHead[i].oldY = posHead[i].y;
		posHead[i].oldX = posHead[i].x;
		posHead[i].x = posHead[i + 1].oldX;
		posHead[i].y = posHead[i + 1].oldY;

		posTail[i].oldX = posTail[i].x;
		posTail[i].oldY = posTail[i].y;
		posTail[i].x = posHead[i].oldX;
		posTail[i].y = posHead[i].oldY;

	}
	//убняр
	posHead[snakeLen - 1].oldY = posHead[snakeLen - 1].y;
	posHead[snakeLen - 1].oldX = posHead[snakeLen - 1].x;
	posHead[snakeLen - 1].x -= 10;
	posHead[snakeLen - 1].y = posHead[snakeLen - 1].oldY;//

	posTail[snakeLen - 1].oldX = posTail[snakeLen - 1].x;
	posTail[snakeLen - 1].oldY = posTail[snakeLen - 1].y;
	posTail[snakeLen - 1].x = posHead[snakeLen - 1].oldX;
	posTail[snakeLen - 1].y = posHead[snakeLen - 1].oldY;//
}

void SNAKE::moveRight()
{
	for (int i = 0; i < snakeLen - 1; i++)
	{
		posHead[i].oldY = posHead[i].y;
		posHead[i].oldX = posHead[i].x;
		posHead[i].x = posHead[i + 1].oldX;
		posHead[i].y = posHead[i + 1].oldY;

		posTail[i].oldX = posTail[i].x;
		posTail[i].oldY = posTail[i].y;
		posTail[i].x = posHead[i].oldX;
		posTail[i].y = posHead[i].oldY;
	}
	//убняр
	posHead[snakeLen - 1].oldY = posHead[snakeLen - 1].y;
	posHead[snakeLen - 1].oldX = posHead[snakeLen - 1].x;
	posHead[snakeLen - 1].x += 10;
	posHead[snakeLen - 1].y = posHead[snakeLen - 1].oldY;//

	posTail[snakeLen - 1].oldX = posTail[snakeLen - 1].x;
	posTail[snakeLen - 1].oldY = posTail[snakeLen - 1].y;
	posTail[snakeLen - 1].x = posHead[snakeLen - 1].oldX;
	posTail[snakeLen - 1].y = posHead[snakeLen - 1].oldY;//
}

void SNAKE::moveTop()
{
	for (int i = 0; i < snakeLen-1; i++)
	{
		posHead[i].oldY = posHead[i].y;
		posHead[i].oldX = posHead[i].x;
		posHead[i].x = posHead[i+1].oldX;
		posHead[i].y = posHead[i + 1].oldY;

		posTail[i].oldX = posTail[i].x;
		posTail[i].oldY = posTail[i].y;
		posTail[i].x = posHead[i].oldX;
		posTail[i].y = posHead[i].oldY;

	}
	//убняр
	posHead[snakeLen-1].oldY = posHead[snakeLen - 1].y;
	posHead[snakeLen - 1].oldX = posHead[snakeLen - 1].x;
	posHead[snakeLen - 1].x = posHead[snakeLen - 1].oldX;
	posHead[snakeLen - 1].y -= 10;//

	posTail[snakeLen - 1].oldX = posTail[snakeLen - 1].x;
	posTail[snakeLen - 1].oldY = posTail[snakeLen - 1].y;
	posTail[snakeLen - 1].x = posHead[snakeLen - 1].oldX;
	posTail[snakeLen - 1].y = posHead[snakeLen - 1].oldY;//
}

void SNAKE::moveBottom()
{
	for (int i = 0; i < snakeLen-1; i++)
	{
		posHead[i].oldX = posHead[i].x;
		posHead[i].oldY = posHead[i].y;
		posHead[i].y = posHead[i+1].oldY;
		posHead[i].x = posHead[i+1].oldX;

		posTail[i].oldX = posTail[i].x;
		posTail[i].oldY = posTail[i].y;
		posTail[i].y = posHead[i].oldY;
		posTail[i].x = posHead[i].oldX;
	}
	//убняр
	posHead[snakeLen - 1].oldY = posHead[snakeLen - 1].y;
	posHead[snakeLen - 1].oldX = posHead[snakeLen - 1].x;
	posHead[snakeLen - 1].x = posHead[snakeLen - 1].oldX ;
	posHead[snakeLen - 1].y += 10;//

	posTail[snakeLen - 1].oldX = posTail[snakeLen - 1].x;
	posTail[snakeLen - 1].oldY = posTail[snakeLen - 1].y;
	posTail[snakeLen - 1].x = posHead[snakeLen - 1].oldX;
	posTail[snakeLen - 1].y = posHead[snakeLen - 1].oldY;//
}

void SNAKE::upSize(int key, int keyCache)
{
	snakeLen++;
	coords *newPtrPosH = new coords[snakeLen+1];
	coords *newPtrPosT = new coords[snakeLen+1];
	for (int i = 0; i < snakeLen; i++)
	{
		newPtrPosH[i+1] = posHead[i];
		newPtrPosT[i+1] = posTail[i];
	}
	switch (key)
	{
	case 75://Left
		if (keyCache != 77)
		{
			newPtrPosH[0].y = newPtrPosH[1].oldY;
			newPtrPosH[0].x = newPtrPosH[1].oldX;
			newPtrPosH[0].oldX = newPtrPosH[0].x-10;
			newPtrPosH[0].oldY = newPtrPosH[0].y;

			newPtrPosT[0].x = newPtrPosT[1].oldX;
			newPtrPosT[0].y = newPtrPosT[1].oldY;
			newPtrPosT[0].oldX = newPtrPosT[0].x - 10;
			newPtrPosT[0].oldY = newPtrPosT[0].y;
		}
		else
		{//Right
			newPtrPosH[0].y = newPtrPosH[1].oldY;
			newPtrPosH[0].x = newPtrPosH[1].oldX;
			newPtrPosH[0].oldX = newPtrPosH[0].x+10;
			newPtrPosH[0].oldY = newPtrPosH[0].y;

			newPtrPosT[0].oldX = newPtrPosT[1].x;
			newPtrPosT[0].oldY = newPtrPosT[1].y;
			newPtrPosT[0].x = newPtrPosT[1].x - 10;
			newPtrPosT[0].y = newPtrPosT[0].oldY;
		}
		break;
	case 72://top
		if (keyCache != 80)
		{
			newPtrPosH[0].y = newPtrPosH[1].oldY;
			newPtrPosH[0].x = newPtrPosH[1].oldX;
			newPtrPosH[0].oldX = newPtrPosH[0].x;
			newPtrPosH[0].oldY = newPtrPosH[0].y+10;

			newPtrPosT[0].x = newPtrPosT[1].oldX;
			newPtrPosT[0].y = newPtrPosT[1].oldY;
			newPtrPosT[0].oldX = newPtrPosT[0].x;
			newPtrPosT[0].oldY = newPtrPosT[0].y-10;
			//s1.moveTop();
		}
		else
		{
			newPtrPosH[0].y = newPtrPosH[1].oldY;
			newPtrPosH[0].x = newPtrPosH[1].oldX;
			newPtrPosH[0].oldX = newPtrPosH[0].x;
			newPtrPosH[0].oldY = newPtrPosH[0].y + 10;

			newPtrPosT[0].x = newPtrPosT[1].oldX;
			newPtrPosT[0].y = newPtrPosT[1].oldY;
			newPtrPosT[0].oldX = newPtrPosT[0].x;
			newPtrPosT[0].oldY = newPtrPosT[0].y - 10;
		}
			//s1.moveBottom();
			break;
	case 77://right
		if (keyCache != 75)
		{
			newPtrPosH[0].y = newPtrPosH[1].oldY;
			newPtrPosH[0].x = newPtrPosH[1].oldX;
			newPtrPosH[0].oldX = newPtrPosH[0].x + 10;
			newPtrPosH[0].oldY = newPtrPosH[0].y;

			newPtrPosT[0].oldX = newPtrPosT[1].x;
			newPtrPosT[0].oldY = newPtrPosT[1].y;
			newPtrPosT[0].x = newPtrPosT[1].x + 10;
			newPtrPosT[0].y = newPtrPosT[0].oldY;
			//s1.moveRight();
		}
		else
		{
			newPtrPosH[0].y = newPtrPosH[1].oldY;
			newPtrPosH[0].x = newPtrPosH[1].oldX;
			newPtrPosH[0].oldX = newPtrPosH[0].x - 10;
			newPtrPosH[0].oldY = newPtrPosH[0].y;

			newPtrPosT[0].x = newPtrPosT[1].oldX;
			newPtrPosT[0].y = newPtrPosT[1].oldY;
			newPtrPosT[0].oldX = newPtrPosT[0].x - 10;
			newPtrPosT[0].oldY = newPtrPosT[0].y;
		}
			//s1.moveLeft();
			break;
	case 80://bottom
		if (keyCache != 72)
		{
			newPtrPosH[0].y = newPtrPosH[1].oldY;
			newPtrPosH[0].x = newPtrPosH[1].oldX;
			newPtrPosH[0].oldX = newPtrPosH[0].x;
			newPtrPosH[0].oldY = newPtrPosH[0].y - 10;

			newPtrPosT[0].x = newPtrPosT[1].oldX;
			newPtrPosT[0].y = newPtrPosT[1].oldY;
			newPtrPosT[0].oldX = newPtrPosT[0].x;
			newPtrPosT[0].oldY = newPtrPosT[0].y - 10;
			//s1.moveBottom();
		}
		else
		{
			newPtrPosH[0].y = newPtrPosH[1].oldY;
			newPtrPosH[0].x = newPtrPosH[1].oldX;
			newPtrPosH[0].oldX = newPtrPosH[0].x;
			newPtrPosH[0].oldY = newPtrPosH[0].y + 10;

			newPtrPosT[0].x = newPtrPosT[1].oldX;
			newPtrPosT[0].y = newPtrPosT[1].oldY;
			newPtrPosT[0].oldX = newPtrPosT[0].x;
			newPtrPosT[0].oldY = newPtrPosT[0].y + 10;
		}
			//s1.moveTop();
			break;
		//newPtrPosH[0].x = posHead[0].oldX;
		//newPtrPosT[0].y = posTail[0].oldY;
		//newPtrPosH[0].oldX = posHead[0].x-10;
		
	}
	newPtrPosT[0].oldY = posTail[0].y-10;
	if (snakeLen > 0)
	{
		delete[] posHead;
		delete[] posTail;
	}
	posHead = newPtrPosH;
	posTail = newPtrPosT;
}

int SNAKE::getLen()
{
	return snakeLen;
}

SNAKE::~SNAKE()
{
	delete[] posHead;
	delete[] posTail;
}
