#pragma once

struct coords
{
    int x;
    int y;
    int oldX;
    int oldY;
};

class SNAKE
{
private:
    coords* posHead;
    coords* posTail;
    int snakeLen;
public:

    /*����������� �� ���������*/
    SNAKE();

    int getHeadPosX(int i);
    int getHeadPosY(int i);
    int getHeadPosOldX(int i);
    int getHeadPosOldY(int i);

    int getTailPosX(int i);
    int getTailPosY(int i);
    int getTailPosOldX(int i);
    int getTailPosOldY(int i);

    void setPos(coords* _Head, coords* _Tail);

    void moveLeft();

    void moveRight();

    void moveTop();

    void moveBottom();

    void upSize(int key, int keyCache);

    int getLen();
    /*����������� �����������*/
    //NEWCLS(const NEWCLS&);

    /*����������*/
    ~SNAKE();

};