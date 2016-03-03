
#include <Windows.h>
#include "LinkList.h"

// 蛇的状态
#define SNAKE_MOVED			0
#define SNAKE_DEAD			1
#define SNAKE_COMPLETE		2
#define SNAKE_EATEN_FOOD	3
#define SNAKE_GROWUP		4
#define SNAKE_ERROR			5

// 蛇的方向
enum dirction
{
	SNAKE_UP,
	SNAKE_DOWN,
	SNAKE_LEFT,
	SNAKE_RIGHT,
};

// 游戏坐标
typedef struct _GAME_COORD
{
	short x;
	short y;
}GAME_COORD, *PGAME_COORD;

// 函数声明

/// snake_and_food.c中的接口函数
void SetBoundary(int x, int y);
PGAME_COORD GetBoundary();

int CreateFood();
PGAME_COORD GetFood();

void SetDirction(dirction dir);
dirction GetDirction();

void CreateSnake(dirction dir, int head_x, int head_y, int init_len);
int SnakeGorwup();
int SnakeMove();
int GetSnakeSize();
PGAME_COORD GetSnakeHead();
PGAME_COORD GetSnakeTail();
PGAME_COORD GetSnakeAt(int n);
void DistroySnake();

/// game_opration.c 中的接口函数
int GetScore();
int GetLevel();
void CreateGame(HWND hwnd,
	DWORD dwInitTimerElapse,
	unsigned int one_level_scores,
	DOUBLE level_speedup_ratio,
	int boundary_x, int boundary_y,
	int init_x, int init_y,
	int init_len,
	dirction init_dir);
void OnTimer(HWND hwnd);
void OnKeyDown(DWORD vk);