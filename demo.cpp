#include<conio.h>
//#include<iostream>
//#include<cstring>
#include<windows.h>
//#include<WinUser.h>
//#include<cstdlib>
#include <thread>
#include "Snake.h"
#include "SnakeFood.h"

//��������� ����
void drawSnake(SNAKE& s, HDC hDC, HPEN hPenBlck, HPEN hPen, HPEN HSpen);
//��������� ���
void drawApple(SnakeFood apple, HDC hDC, HPEN hPenApple);
//��� ��������� ����������� ��������� ����� ��� ������� ������������ ����������
void threadDraw(int& SleepCounter, int &Score, SNAKE* s1, SnakeFood* apple, int key, int keyCache,
	HDC hDC, RECT rc);

int main()
{

	int indexIter(0);
	bool varEnd = false;
	int ScoreCount(0);
	int SleepCounter(100);

	//��� ������� ��� �������
	int keyCache(0);
	//��� �������
	int key(0);

	HWND hWnd = GetConsoleWindow();
	// �������� DC ��� ���������
	HDC hDC = GetDC(hWnd);
	srand(time(0));
	//��������� ���� �������
	SetConsoleTitle(L"SNAKE");


	//���������
	HFONT bigFont = CreateFont(50, 20, 0, 0, 700, 0, 0, 0,
		DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE, (L"Arial"));

	HFONT LittleFont = CreateFont(30, 12, 0, 0, 500, 0, 0, 0,
		DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE, (L"Arial"));

	HFONT bigFont1 = CreateFont(50, 20, 30, 0, 700, 0, 1, 0,
		DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE, (L"Arial"));
	// �������� ������ ���������� ������� ����
	RECT rc;
	//GetClientRect(hWnd, &rc);
	GetWindowRect(hWnd, &rc);
	//�������������� �������
	RECT textRect;
	RECT textRectScore;
	RECT TitleRect;
	RECT helpRect;

	SetRect(&TitleRect, rc.right + 350, 0, 0, 0);
	SetRect(&textRect, rc.right + 180, rc.top+50, 0, 0);
	SetRect(&textRectScore, textRect.left * 1.2, rc.top+50, 0, 0);
	SetRect(&helpRect, rc.right + 350, rc.top + 150, 0, 0);

	SNAKE s1;
	SnakeFood apple;

	//������ ���������� ���������� (10,20,100,490...)
	apple.setX((int)(ceil(10 + rand() % (rc.right / 2 - 110))));
	apple.setY((int)(ceil(10 + rand() % (rc.bottom - rc.top - 110))));


	bool start = false;

	//�������� ���� ������� � ������������ ��������
	system("Color 07");
	ReleaseDC(hWnd, hDC);
	
	//��������� ������ � ������ ����� �������/////////////////////////////////////////
	hWnd = GetConsoleWindow();
	hDC = GetDC(hWnd);
	SelectObject(hDC, LittleFont);
	DrawText(hDC, TEXT("Use arrows for move,\n esc- exit,\n any other key for pause"),
		-1, &helpRect, DT_CENTER | DT_NOCLIP);
	DrawText(hDC, TEXT("Use arrows for move,\n esc- exit,\n any other key for pause"),
		-1, &helpRect, DT_CENTER | DT_NOCLIP);
	//ReleaseDC(hWnd, hDC);
	//hWnd = GetConsoleWindow();
	//hDC = GetDC(hWnd);

	//����� ��������
	SelectObject(hDC, bigFont1);
	DrawText(hDC, TEXT("SNAKE::console"), -1, &TitleRect, DT_CENTER | DT_NOCLIP);
	ReleaseDC(hWnd, hDC);
	hWnd = GetConsoleWindow();
	hDC = GetDC(hWnd);

	SelectObject(hDC, LittleFont);
	DrawText(hDC, TEXT("Use arrows for move,\n esc- exit,\n any other key for pause"),
		-1, &helpRect, DT_CENTER | DT_NOCLIP);

	//����� ���� �����
	SelectObject(hDC, bigFont);
	DrawText(hDC, TEXT("score is "), -1, &textRect, DT_CENTER | DT_NOCLIP);
	ReleaseDC(hWnd, hDC);
	hWnd = GetConsoleWindow();
	hDC = GetDC(hWnd);
	//////////////////////////////////////////////////////////////////////////////////
	
	//��������� ������////////////////////////////////////////|
	HPEN LinePen = CreatePen(PS_SOLID, 3, RGB(156, 255, 140));
	SelectObject(hDC, LinePen);// ��������� ���� 

	MoveToEx(hDC, 0, 0, NULL);
	LineTo(hDC, rc.right / 2, 0);

	MoveToEx(hDC, rc.right / 2, 0, NULL);
	LineTo(hDC, rc.right / 2, rc.bottom - rc.top - 100);

	MoveToEx(hDC, 0, rc.bottom - rc.top - 100, NULL);
	LineTo(hDC, rc.right / 2, rc.bottom - rc.top - 100);

	MoveToEx(hDC, 0, 0, NULL);
	LineTo(hDC, 0, rc.bottom - rc.top - 100);

	/////////////////////////////////////////////////////////|

	//����� �� ����� - "ESC"
	while (varEnd != true)
	{
		//��������� ��������� �������������� � ������
		std::thread thrInp(threadDraw, std::ref(SleepCounter),
			std::ref(ScoreCount), &s1, &apple, key, keyCache, hDC, rc);

		bool someKeyPress = _kbhit();
		//��������� ��������, ���������� ������� �������
		if (someKeyPress)
		{
			key = _getch();
			if (key == 224)//��������� ������� �������
			{
				key = _getch();
				start = true;
			}
		}
		switch (key)
		{
		case 75://Left
			if (keyCache != 77)
			{
				keyCache = key;
				s1.moveLeft();
			}
			else s1.moveRight();
			break;
		case 72://top
			if (keyCache != 80)
			{
				keyCache = key;
				s1.moveTop();
			}
			else
				s1.moveBottom();
			break;
		case 77://right
			if (keyCache != 75)
			{
				keyCache = key;
				s1.moveRight();
			}
			else
				s1.moveLeft();
			break;
		case 80://bottom
			if (keyCache != 72)
			{
				keyCache = key;
				s1.moveBottom();
			}
			else
				s1.moveTop();
			break;
		// 27 = "Esc"
		case 27:
			printf_s("Game Over!\n");
			varEnd = true;
			break;
		default:
			break;
		}
		//�������� ������ �� ������� (������ ����� ������ ��������)
		if (start)
		{
			if (s1.getHeadPosX(0) <= 0 || s1.getHeadPosY(0) <= 0 
				|| s1.getHeadPosX(0) >= rc.right / 2 
				|| s1.getHeadPosY(0) >= rc.bottom - rc.top - 100)
			{
				key = 27;
			}
		}
		//�������� �� ���������� ��������� ������ � ����� �� ������ ������
		int counter(0);
		for (int i = 0; i < s1.getLen() - 1; i++)
		{
			for (int j = i + 1; j < s1.getLen() - 1; j++)
			{
				if (s1.getHeadPosX(i) == s1.getHeadPosX(j) 
					&& s1.getHeadPosY(i) == s1.getHeadPosY(j))
				{
					counter++;
				}
			}
		}
		//� ������ ����������- �����
		if (counter == 1)
		{
			key = 27;
		}
		//������������� ������ ���������
		thrInp.join();

		//��������� ��������//////////////////////////////////////////////////////
		wchar_t istr[4];
		_itow_s(ScoreCount, istr, 10);
		SelectObject(hDC, bigFont);
		//��������� ������������ �� ���������
		//DrawText(hDC, TEXT("score is "), -1, &textRect, DT_CENTER | DT_NOCLIP);
		DrawTextW(hDC, istr, -1, &textRectScore, DT_CENTER | DT_NOCLIP);
		ReleaseDC(hWnd, hDC);
		hWnd = GetConsoleWindow();
		hDC = GetDC(hWnd);
		//////////////////////////////////////////////////////////////////////////
	}

	//����� ����������� ����������
	do
	{
		key = 0;
		bool someKeyPress = _kbhit();
		//��������� ��������
		if (someKeyPress)
		{
			key = _getch();
			if (key == 59)
			{
				printf_s("apple X:%d, y:%d\n", apple.getX(), apple.getY());
				system("pause");
			}
		}
	} while (key == 0);

	// ����������� DC
	ReleaseDC(hWnd, hDC);
}
	

//��������� � ��������� ������
void threadDraw(int& SleepCounter, int& Score, SNAKE* s1, SnakeFood* apple, int key, int keyCache,
	HDC hDC, RECT rc)
{
	// ������� Pen
	HPEN hPen = CreatePen(PS_SOLID, 5, RGB(0, 255, 0));
	//������ ����
	HPEN HSpen = CreatePen(PS_SOLID, 5, RGB(151, 151, 255));
	//������
	HPEN hPenApple = CreatePen(PS_SOLID, 5, RGB(255, 0, 0));
	//������������ ������������ ���� �������
	HPEN hPenBlck = CreatePen(PS_SOLID, 5, RGB(0, 0, 0));

	HPEN hOldPen = (HPEN)SelectObject(hDC, hPenBlck);
	//�����������
	srand(time(0));

	//� ������� Sleep ���������� ����������� �������� ���������,
	//������ ��� ���� �������� ���������, ������� ���������
	Sleep(SleepCounter);
	int len = s1->getLen();
	drawSnake(*s1, hDC, hPenBlck, hPen, HSpen);
	if (Score == 0)
	{
		//��������� ��� ������ ����
		drawApple(*apple, hDC, hPenApple);
	}
	//�������� ���������� ��������� ������ � ������
	if (apple->getX() == s1->getHeadPosX(len - 1) && apple->getY() == s1->getHeadPosY(len - 1))
	{
		//���� ���� ������ �� ����������� ��������
		if (Score != 0 && Score % 2 == 0)
		{
			SleepCounter -= 1;
		}
		Score += 1;
		s1->upSize(key, keyCache);
		hOldPen = (HPEN)SelectObject(hDC, hPenBlck);
		//�������� ���������� ������
		MoveToEx(hDC, apple->getX(), apple->getY(), NULL);
		LineTo(hDC, apple->getX(), apple->getY());
		//�����(��� ��������������� rand() ������ ������ �������� ������ � ����
			  //30->50->80->...->400->0->....)??????
		rand();

		//������ ������ ������
		bool check = true;
		//������ ����� ��������� ���� � ��������� �� ����� � ����/////////////////////////////////
		do
		{
			check = true;
			apple->setX((int)(ceil(10 + rand() % (rc.right / 2 - 110))));
			for (int i = 0; i < s1->getLen(); i++)
			{
				if (s1->getHeadPosX(i) == apple->getX() && s1->getHeadPosY(i) == apple->getY())
				{
					check = false;
				}
				if (s1->getTailPosX(i) == apple->getX() && s1->getTailPosY(i) == apple->getY())
				{
					check = false;
				}
			}
		} while (!check);

		do
		{
			check = true;
			apple->setY((int)(ceil(10 + rand() % (rc.bottom - rc.top - 110))));
			for (int i = 0; i < s1->getLen(); i++)
			{
				if (s1->getHeadPosX(i) == apple->getX() && s1->getHeadPosY(i) == apple->getY())
				{
					check = false;
				}
				if (s1->getTailPosX(i) == apple->getX() && s1->getTailPosY(i) == apple->getY())
				{
					check = false;
				}
			}
		} while (!check);
		drawApple(*apple, hDC, hPenApple);
		////////////////////////////////////////////////////////////////////////////////////////
	}
	//�������
	DeleteObject(hPen);
	DeleteObject(HSpen);
	DeleteObject(hPenApple);
	DeleteObject(hOldPen);
	DeleteObject(hPenBlck);

}

//��������� � �������� ������ ������
void drawSnake(SNAKE& s, HDC hDC, HPEN hPenBlck, HPEN hPen, HPEN HSpen)
{
	// ������� Pen
	HPEN hOldPen = (HPEN)SelectObject(hDC, hPen);
	MoveToEx(hDC, s.getTailPosX(0), s.getTailPosY(0), NULL);
	//����� ����
	int len = s.getLen();

	//��������� ����� �����
	for (int i = 0; i < len-1; i++)
	{
		MoveToEx(hDC, s.getHeadPosX(i), s.getHeadPosY(i), NULL);
		LineTo(hDC, s.getTailPosX(i), s.getTailPosY(i));//��������
	}
	hOldPen = (HPEN)SelectObject(hDC, HSpen);
	MoveToEx(hDC, s.getHeadPosX(len-1), s.getHeadPosY(len-1), NULL);
	LineTo(hDC, s.getTailPosX(len-1), s.getTailPosY(len-1));//��������
	//������������ �������
	hOldPen = (HPEN)SelectObject(hDC, hPenBlck);
	MoveToEx(hDC, s.getHeadPosOldX(0), s.getHeadPosOldY(0), NULL);
	LineTo(hDC, s.getTailPosOldX(0), s.getTailPosOldY(0));
}

//��������� ����
void drawApple(SnakeFood apple, HDC hDC, HPEN hPenApple)
{
	HPEN hOldPen = (HPEN)SelectObject(hDC, hPenApple);
	MoveToEx(hDC, apple.getX(), apple.getY(), NULL);
	LineTo(hDC, apple.getX(), apple.getY());
}
