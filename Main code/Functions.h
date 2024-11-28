#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#define LEFT 3
#define TOP 1
#define RIGHT LEFT+BOARD_SIZE*4
#define BOTTOM TOP+BOARD_SIZE*2
// 1 o co kich thuoc la 4x2 (ngang 4 dai 2)
#define BOARD_SIZE 12


#include <conio.h>
#include <ctype.h>
#include <iostream>
#include <windows.h>
using namespace std;

struct Cursor {
    COORD coord;
};

struct CursorRemove {
    COORD coord;
};

struct XO{
    COORD X[200], O[200];
    int nX = 0, nO = 0;
};


struct _POINT {
    int x , y, c;
};




//Control
void StartGame();
void ExitGame();
void MoveRight();
void MoveLeft();
void MoveDown();
void MoveUp();

void moveWASD();

//View
void GotoXY(int, int);
void FixConsoleWindow();
void DrawBoard();
int ProcessFinish(int);
int AskContinue();


// void veBanCo();



//Model
void ResetData();
void GarbageCollect();
int TestBoard();
int CheckBoard(int, int);
#endif