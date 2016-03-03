#include <Windows.h>
#include "snake.h"

// 计时器ID。
#define TIMER_ID 12340

DWORD dwTimeInterval;
double dbSpeedUpRatio;
int level_up_period;


int score = 0;
int level = 0;

#define IS_SPEEDUP(size) (size % level_up_period) == 0

int GetScore()
{
	return score;
}

int GetLevel()
{
	return level;
}

// 提高速度。
BOOL SpeedUp(HWND hwnd)
{
	dwTimeInterval = (DWORD)(dwTimeInterval *0.9);
	KillTimer(hwnd, TIMER_ID);
	SetTimer(hwnd, TIMER_ID, dwTimeInterval, NULL);
	return TRUE;
}

// 在计时器的驱动下
// 当计时器发生时进行的处理逻辑。
void OnTimer(HWND hwnd)
{
	switch (SnakeMove())
	{
	case SNAKE_DEAD:
		// 如果蛇已经死了，首先关闭计时器，避免再次调用SnakeMove。
		KillTimer(hwnd, TIMER_ID);
		// 然后通知玩家，Game Over了，退出进程。
		MessageBox(0, "Game Over", "Game Over", 0);
		ExitProcess(0);
		break;

	case SNAKE_EATEN_FOOD:
		score++;
		CreateFood();
		switch (SnakeGorwup())
		{
		case SNAKE_COMPLETE:
			// 如果蛇已经死了，首先关闭计时器，避免再次调用SnakeMove。
			KillTimer(hwnd, TIMER_ID);
			// 然后通知玩家，Game Over了，退出进程。
			MessageBox(0, "You Win!", "You Win", 0);
			ExitProcess(0);
			break;
		case SNAKE_ERROR:
			KillTimer(hwnd, TIMER_ID);
			MessageBox(hwnd, "Error!!", "Error!1", MB_OK);
			ExitProcess(0);
			break;
		case SNAKE_GROWUP:
			if (IS_SPEEDUP(GetSnakeSize()))
			{
				level++;
			}
			break;
		}
		InvalidateRect(hwnd, NULL, 1);
		UpdateWindow(hwnd);
		break;
	case SNAKE_MOVED:
		// 设置窗口重绘制，更新窗口
		// If this parameter is NULL, the entire client area is added to 
		// the update region.
		InvalidateRect(hwnd, NULL, 1);
		UpdateWindow(hwnd);
		break;
	}
	return;

}
// 当用于操作时进行的逻辑处理。
// 本游戏只使用到了键盘上下左右键控制。
void OnKeyDown(DWORD vk)
{
	switch (vk)
	{
	case VK_LEFT:
		SetDirction(SNAKE_LEFT);
		break;
	case VK_RIGHT:
		SetDirction(SNAKE_RIGHT);
		break;
	case VK_UP:
		SetDirction(SNAKE_UP);
		break;
	case VK_DOWN:
		SetDirction(SNAKE_DOWN);
		break;
	default:
		break;
	}
	return;
}


// 程序启动以后进行的初始化操作。
void CreateGame(HWND hwnd, 
	int init_timer_interval, int period, double speedup_ratio,
	int max_x, int max_y, int init_x, int init_y, 
	int init_len, dirction init_dir)
{
	// 设置随机数种子
	// 食物的位置是随机的。
	FILETIME ft;
	GetSystemTimeAsFileTime(&ft);
	srand(ft.dwLowDateTime);

	// 创建一个计时器
	// 每300毫秒，hwnd窗口（本窗口）就会收到一个WM_TIMER消息。
	// 通过TIMER使得程序可以时间周期性的刷新游戏。
	// 这是Windows“事件驱动型”程序架构的一种体现
	dbSpeedUpRatio = speedup_ratio;
	dwTimeInterval = init_timer_interval;
	level_up_period = period;

	SetBoundary(max_x, max_y);

	//snake
	SetTimer(hwnd, TIMER_ID, dwTimeInterval, NULL);

	// 创建表示贪吃蛇的数据结构
	CreateSnake(init_dir, init_x, init_y, 5);

	// 创建表示食物的数据结构
	CreateFood();
}