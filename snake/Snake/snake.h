
#include <Windows.h>
#include "LinkList.h"


#define CELLS_X 20
#define CELLS_Y 20

// ÉßµÄ×´Ì¬
#define SNAKE_MOVED		0
#define SNAKE_DEAD		1
#define SNAKE_COMPLETE	2
#define SNAKE_GROWUP	3
#define SNAKE_LEVELUP	4
#define SNAKE_ERROR		5


enum dirction
{
	SNAKE_UP,
	SNAKE_DOWN,
	SNAKE_LEFT,
	SNAKE_RIGHT,
};

typedef struct _GAME_COORD
{
	short x;
	short y;
}GAME_COORD, *PGAME_COORD;

// º¯ÊýÉùÃ÷
int CoordEqual(PGAME_COORD one, PGAME_COORD two);
void SetDirction(dirction dir);
int SnakeGorwup();
int CreateFood();
int CreateSnake(dirction dir, int head_x, int head_y, int level_up, int init_len);
int SnakeMove();

dirction GetDirction();
int GetScore();
int GetLevel();
PLIST GetSnakeList();
PGAME_COORD GetFood();

void OnCreate(HWND hwnd);
void OnTimer(HWND hwnd);
void OnKeyDown(DWORD vk);