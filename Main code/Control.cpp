#include "Functions.h"

extern _POINT _A[BOARD_SIZE][BOARD_SIZE];
extern bool _TURN;
extern int _COMMAND;
extern int _X, _Y;

void StartGame() {
    system("cls");
    ResetData();

    DrawBoard();
}

void ExitGame() {
    system("cls");
    GarbageCollect();
}

void MoveRight() {
    if (_X < _A[BOARD_SIZE - 1][BOARD_SIZE - 1].x)
    {
        _X += 4;
        GotoXY(_X, _Y);
    }
}

void MoveLeft() {
    if (_X > _A[0][0].x)
    {
        _X -= 4;
        GotoXY(_X, _Y);
    }
}

void MoveDown() {
    if (_Y < _A[BOARD_SIZE - 1][BOARD_SIZE - 1].y)
    {
        _Y += 2;
        GotoXY(_X, _Y);
    }
}

void MoveUp() {
    if (_Y > _A[0][0].y)
    {
        _Y -= 2;
        GotoXY(_X, _Y);
    }
}

void moveWASD()
{
   bool validEnter = true;
   while(1) {
        _COMMAND = toupper(getch());
        // xet tung nut bam
        switch(_COMMAND) {
            case 27: { // phim esc la 27
                ExitGame();
                return;
            }
            // WASD cho X, mui ten cho O
            // nut danh luot X (_TURN true)
            case 'A': { 
                if(_TURN) MoveLeft();
                break;
            }
            case 'W': { 
                if(_TURN) MoveUp();
                break;
            }
            case 'S': { 
                if(_TURN) MoveDown();
                break;
            }
            case 'D': {
                if(_TURN) MoveRight();
                break;
            }
            // _TURN false (luot O)
            case 75: {          // left arrow: 75
                if(!_TURN) MoveLeft();
                break;
            }
            case 72: {          // up arrow: 72
                if(!_TURN) MoveUp();
                break;
            }
            case 80: {          // right arrow: 80
                if(!_TURN) MoveDown();
                break;
            }
            case 77: {          // down arrow: 77
                if(!_TURN) MoveRight();
                break;
            }
            // press Enter
            case 13: {
                switch (CheckBoard(_X, _Y)) 
                {
                case -1:
                    cout << "X";
                    break;
                
                case 1:
                    cout << "O";
                    break;
                
                case 0:
                    validEnter = false; //danh vao o dah roi
                }
                // check win/lose/draw/continue
                if (validEnter == true)
                {
                    switch (ProcessFinish(TestBoard()))
                    {
                    case -1: case 1: case 0:
                        if (AskContinue() != 'Y')
                        {
                            ExitGame();
                            return;
                        }
                        else
                            StartGame();
                    }
                }
                validEnter = true; // unlock
            }
        }
    }
}
//siuuuuu