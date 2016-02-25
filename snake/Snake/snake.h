
#include <Windows.h>
#include "LinkList.h"


#define CELLS_X 20
#define CELLS_Y 20

// ÉßµÄ×´Ì¬
#define SNAKE_MOVED		0
#define SNAKE_DEAD		1
#define SNAKE_COMPLETE	2
#define SNAKE_GROWUP	3

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
int IsCoincide(POSITION one, POSITION two);
void SetDirction(dirction dir);
int SnakeGorwup();
int CreateFood();
int CreateSnake();
int SnakeMove();