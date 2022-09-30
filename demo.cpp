#include<conio.h>
//#include<iostream>
//#include<cstring>
#include<windows.h>
//#include<WinUser.h>
//#include<cstdlib>
#include <thread>
#include "Snake.h"
#include "SnakeFood.h"

//Отрисовка змеи
void drawSnake(SNAKE& s, HDC hDC, HPEN hPenBlck, HPEN hPen, HPEN HSpen);
//Отрисовка еды
void drawApple(SnakeFood apple, HDC hDC, HPEN hPenApple);
//Для отрисовки использован отдельный поток для большей отзывчивости управления
void threadDraw(int& SleepCounter, int &Score, SNAKE* s1, SnakeFood* apple, int key, int keyCache,
	HDC hDC, RECT rc);

int main()
{

	int indexIter(0);
	bool varEnd = false;
	int ScoreCount(0);
	int SleepCounter(100);

	//Код клавиши для стрелок
	int keyCache(0);
	//Код клавиши
	int key(0);

	HWND hWnd = GetConsoleWindow();
	// Получаем DC для рисования
	HDC hDC = GetDC(hWnd);
	srand(time(0));
	//Заголовок окна консоли
	SetConsoleTitle(L"SNAKE");


	//Заголовок
	HFONT bigFont = CreateFont(50, 20, 0, 0, 700, 0, 0, 0,
		DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE, (L"Arial"));

	HFONT LittleFont = CreateFont(30, 12, 0, 0, 500, 0, 0, 0,
		DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE, (L"Arial"));

	HFONT bigFont1 = CreateFont(50, 20, 30, 0, 700, 0, 1, 0,
		DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE, (L"Arial"));
	// Получаем размер клиентской области окна
	RECT rc;
	//GetClientRect(hWnd, &rc);
	GetWindowRect(hWnd, &rc);
	//Информационная область
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

	//Только десятичные координаты (10,20,100,490...)
	apple.setX((int)(ceil(10 + rand() % (rc.right / 2 - 110))));
	apple.setY((int)(ceil(10 + rand() % (rc.bottom - rc.top - 110))));


	bool start = false;

	//Приводим цвет консоли к стандартному значению
	system("Color 07");
	ReleaseDC(hWnd, hDC);
	
	//Отрисовка текста в правой части консоли/////////////////////////////////////////
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

	//Вывод названия
	SelectObject(hDC, bigFont1);
	DrawText(hDC, TEXT("SNAKE::console"), -1, &TitleRect, DT_CENTER | DT_NOCLIP);
	ReleaseDC(hWnd, hDC);
	hWnd = GetConsoleWindow();
	hDC = GetDC(hWnd);

	SelectObject(hDC, LittleFont);
	DrawText(hDC, TEXT("Use arrows for move,\n esc- exit,\n any other key for pause"),
		-1, &helpRect, DT_CENTER | DT_NOCLIP);

	//Вывод поля счёта
	SelectObject(hDC, bigFont);
	DrawText(hDC, TEXT("score is "), -1, &textRect, DT_CENTER | DT_NOCLIP);
	ReleaseDC(hWnd, hDC);
	hWnd = GetConsoleWindow();
	hDC = GetDC(hWnd);
	//////////////////////////////////////////////////////////////////////////////////
	
	//Отрисовка границ////////////////////////////////////////|
	HPEN LinePen = CreatePen(PS_SOLID, 3, RGB(156, 255, 140));
	SelectObject(hDC, LinePen);// указываем перо 

	MoveToEx(hDC, 0, 0, NULL);
	LineTo(hDC, rc.right / 2, 0);

	MoveToEx(hDC, rc.right / 2, 0, NULL);
	LineTo(hDC, rc.right / 2, rc.bottom - rc.top - 100);

	MoveToEx(hDC, 0, rc.bottom - rc.top - 100, NULL);
	LineTo(hDC, rc.right / 2, rc.bottom - rc.top - 100);

	MoveToEx(hDC, 0, 0, NULL);
	LineTo(hDC, 0, rc.bottom - rc.top - 100);

	/////////////////////////////////////////////////////////|

	//Выход из цикла - "ESC"
	while (varEnd != true)
	{
		//Процедуры отрисовки обрабатывается в потоке
		std::thread thrInp(threadDraw, std::ref(SleepCounter),
			std::ref(ScoreCount), &s1, &apple, key, keyCache, hDC, rc);

		bool someKeyPress = _kbhit();
		//Обработка движения, считывание нажатой клавиши
		if (someKeyPress)
		{
			key = _getch();
			if (key == 224)//Обработка нажатия стрелки
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
		//Проверка выхода за границу (только после начала движения)
		if (start)
		{
			if (s1.getHeadPosX(0) <= 0 || s1.getHeadPosY(0) <= 0 
				|| s1.getHeadPosX(0) >= rc.right / 2 
				|| s1.getHeadPosY(0) >= rc.bottom - rc.top - 100)
			{
				key = 27;
			}
		}
		//Проверка на совпадение координат головы и любой из частей хвоста
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
		//В случае совпадения- выход
		if (counter == 1)
		{
			key = 27;
		}
		//Присоединение потока отрисовки
		thrInp.join();

		//Отрисовка счётчика//////////////////////////////////////////////////////
		wchar_t istr[4];
		_itow_s(ScoreCount, istr, 10);
		SelectObject(hDC, bigFont);
		//Постоянно отрисовывать не требуется
		//DrawText(hDC, TEXT("score is "), -1, &textRect, DT_CENTER | DT_NOCLIP);
		DrawTextW(hDC, istr, -1, &textRectScore, DT_CENTER | DT_NOCLIP);
		ReleaseDC(hWnd, hDC);
		hWnd = GetConsoleWindow();
		hDC = GetDC(hWnd);
		//////////////////////////////////////////////////////////////////////////
	}

	//Вывод отладночной информации
	do
	{
		key = 0;
		bool someKeyPress = _kbhit();
		//Обработка движения
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

	// Освобождаем DC
	ReleaseDC(hWnd, hDC);
}
	

//Отрисовка в отдельном потоке
void threadDraw(int& SleepCounter, int& Score, SNAKE* s1, SnakeFood* apple, int key, int keyCache,
	HDC hDC, RECT rc)
{
	// Создаем Pen
	HPEN hPen = CreatePen(PS_SOLID, 5, RGB(0, 255, 0));
	//Голова змеи
	HPEN HSpen = CreatePen(PS_SOLID, 5, RGB(151, 151, 255));
	//Яблоко
	HPEN hPenApple = CreatePen(PS_SOLID, 5, RGB(255, 0, 0));
	//Закрашивание стандартного фона консоли
	HPEN hPenBlck = CreatePen(PS_SOLID, 5, RGB(0, 0, 0));

	HPEN hOldPen = (HPEN)SelectObject(hDC, hPenBlck);
	//Рандомайзер
	srand(time(0));

	//С помощью Sleep происходит регулировка скорости отрисовки,
	//каждые два очка ускоряют отрисовку, повышая сложность
	Sleep(SleepCounter);
	int len = s1->getLen();
	drawSnake(*s1, hDC, hPenBlck, hPen, HSpen);
	if (Score == 0)
	{
		//Отрисовка при начале игры
		drawApple(*apple, hDC, hPenApple);
	}
	//Проверка совпадения координат головы и яблока
	if (apple->getX() == s1->getHeadPosX(len - 1) && apple->getY() == s1->getHeadPosY(len - 1))
	{
		//Если счёт чётный то увеличиваем скорость
		if (Score != 0 && Score % 2 == 0)
		{
			SleepCounter -= 1;
		}
		Score += 1;
		s1->upSize(key, keyCache);
		hOldPen = (HPEN)SelectObject(hDC, hPenBlck);
		//Удаление съеденного яблока
		MoveToEx(hDC, apple->getX(), apple->getY(), NULL);
		LineTo(hDC, apple->getX(), apple->getY());
		//Нужно(Без дополнительного rand() рандом иногда работает только в плюс
			  //30->50->80->...->400->0->....)??????
		rand();

		//Рандом нового яблока
		bool check = true;
		//Рандом новых координат цели с проверкой на спавн в змее/////////////////////////////////
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
	//Очистка
	DeleteObject(hPen);
	DeleteObject(HSpen);
	DeleteObject(hPenApple);
	DeleteObject(hOldPen);
	DeleteObject(hPenBlck);

}

//Отрисовка и удаление старых частей
void drawSnake(SNAKE& s, HDC hDC, HPEN hPenBlck, HPEN hPen, HPEN HSpen)
{
	// Создаем Pen
	HPEN hOldPen = (HPEN)SelectObject(hDC, hPen);
	MoveToEx(hDC, s.getTailPosX(0), s.getTailPosY(0), NULL);
	//Длина змеи
	int len = s.getLen();

	//Отрисовка новой части
	for (int i = 0; i < len-1; i++)
	{
		MoveToEx(hDC, s.getHeadPosX(i), s.getHeadPosY(i), NULL);
		LineTo(hDC, s.getTailPosX(i), s.getTailPosY(i));//Движение
	}
	hOldPen = (HPEN)SelectObject(hDC, HSpen);
	MoveToEx(hDC, s.getHeadPosX(len-1), s.getHeadPosY(len-1), NULL);
	LineTo(hDC, s.getTailPosX(len-1), s.getTailPosY(len-1));//Движение
	//Закрашивание области
	hOldPen = (HPEN)SelectObject(hDC, hPenBlck);
	MoveToEx(hDC, s.getHeadPosOldX(0), s.getHeadPosOldY(0), NULL);
	LineTo(hDC, s.getTailPosOldX(0), s.getTailPosOldY(0));
}

//Отрисовка цели
void drawApple(SnakeFood apple, HDC hDC, HPEN hPenApple)
{
	HPEN hOldPen = (HPEN)SelectObject(hDC, hPenApple);
	MoveToEx(hDC, apple.getX(), apple.getY(), NULL);
	LineTo(hDC, apple.getX(), apple.getY());
}
