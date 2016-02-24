
#include <Windows.h>
#include "LinkList.h"


#define CELLS_X 20
#define CELLS_Y 20

enum dirction
{
	SNAKE_UP,
	SNAKE_DOWN,
	SNAKE_LEFT,
	SNAKE_RIGHT,
};

typedef struct _POSITION
{
	short x;
	short y;
}POSITION, *LPPOSITION;


// º¯ÊýÉùÃ÷
bool IsCoincide(POSITION one, POSITION two);
void SetDirction(dirction dir);
bool Gorwup();
bool CreateFood();
bool CreateSnake();
int SnakeMove();