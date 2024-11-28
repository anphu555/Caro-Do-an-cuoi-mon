#include "Functions.h"

_POINT _A[BOARD_SIZE][BOARD_SIZE];
bool _TURN;
int _COMMAND;
int _X, _Y;

int main() {
    FixConsoleWindow();
    StartGame();
    moveWASD();
}