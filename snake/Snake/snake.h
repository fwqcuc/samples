
#include <Windows.h>
#include "LinkList.h"

// ÉßµÄ×´Ì¬
#define SNAKE_MOVED			0
#define SNAKE_DEAD			1
#define SNAKE_COMPLETE		2
#define SNAKE_EATEN_FOOD	3
#define SNAKE_GROWUP		4
#define SNAKE_ERROR			5


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
void SetBoundary(int x, int y);
PGAME_COORD GetBoundary();

void SetDirction(dirction dir);
int SnakeGorwup();
int CreateFood();
int CreateSnake(dirction dir, int head_x, int head_y, int init_len);
int SnakeMove();

dirction GetDirction();
int GetSnakeSize();
PGAME_COORD GetSnakeHead();
PGAME_COORD GetSnakeTail();
PGAME_COORD GetSnakeAt(int n);
PGAME_COORD GetFood();


// IN GAME.C
int GetScore();
int GetLevel();
void CreateGame(HWND hwnd, 
	int init_timer_interval, int period, double speedup_ratio,
	int max_x, int max_y, int init_x, int init_y, 
	int init_len, dirction init_dir);
void OnTimer(HWND hwnd);
void OnKeyDown(DWORD vk);