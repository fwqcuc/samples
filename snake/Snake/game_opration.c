
/************** 头文件 ****************/
#include <Windows.h>
#include "snake.h"

/************** 宏定义 ****************/
// 计时器ID。
#define TIMER_ID 12340
// 判断游戏是否达到升级条件
#define IS_SPEEDUP(s) (s % dwOneLevelScores) == 0

/************** 全局变量 ****************/
// 计时器到时间隔
DWORD dwTimerElapse;
// 每提高一级，计时器时钟周期缩短的比例。
DOUBLE dbLevelSpeedupRatio;
// 此变量表示多少个积分上升一个级别
DWORD dwOneLevelScores;

// 保存计分，初始为0
int score = 0;
// 保存级别，初始为0
int level = 0;


/************** 函数定义 ****************/
// 返回积分
int GetScore(){return score;}

// 返回level
int GetLevel(){return level;}

// 提高速度。
BOOL SpeedUp(HWND hwnd)
{
	// 调整计时器到时时间
	dwTimerElapse = (DWORD)(dwTimerElapse * dbLevelSpeedupRatio);
	KillTimer(hwnd, TIMER_ID);
	SetTimer(hwnd, TIMER_ID, dwTimerElapse, NULL);
	return TRUE;
}


// 游戏控制的一个主要流程。
// 当计时器发生时进行的处理逻辑。
void OnTimer(HWND hwnd)
{
	// 计时器到时以后，蛇移动一步。
	// 根据以后以后的状态，进行后续处理。
	switch (SnakeMove())
	{
	// 如果蛇已经死了
	case SNAKE_DEAD:
		// 首先关闭计时器，避免在计时器的驱动下再次调用本函数
		KillTimer(hwnd, TIMER_ID);
		// 然后通知玩家，Game Over了，退出进程。
		MessageBox(0, "Game Over", "Game Over", 0);
		ExitProcess(0);
		break;
	// 如果蛇吃到了食物
	case SNAKE_EATEN_FOOD:
		// 计分；
		score++;
		// 创建新的食物。食物是一个全局唯一变量。
		CreateFood();
		// 蛇进行生长，然后判断蛇生长以后的状态，进行后续处理。
		switch (SnakeGorwup())
		{
			// 玩家赢了，停止计时器。
		case SNAKE_COMPLETE:		
			KillTimer(hwnd, TIMER_ID);
			// 通知玩家，退出进程，结束游戏。
			MessageBox(0, "You Win!", "You Win", 0);
			ExitProcess(0);
			break;
			// 发生错误，停止计时器，并退出。
		case SNAKE_ERROR:
			KillTimer(hwnd, TIMER_ID);
			MessageBox(hwnd, "Error!!", "Error!1", MB_OK);
			ExitProcess(0);
			break;
			// 没有结束，也没有错误，正常吃到食物。
		case SNAKE_GROWUP:
			// 判断计分，是否升级。
			if (IS_SPEEDUP(score))
			{
				level++;
				SpeedUp(hwnd);
			}
			break;
		} //switch (SnakeGorwup()) 结束
		break;
	case SNAKE_MOVED:
		break;
	}
	return;

}


// 当用于操作时进行的逻辑处理。
// 本游戏只使用到了键盘上下左右键控制。
void OnKeyDown(DWORD vk)
{
	switch (vk) // virtual key value
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
	}
	return;
}


// 游戏的初始化，
// 创建游戏的内部数据结构和系统对象。
void CreateGame(HWND hwnd, // 主窗口句柄
	DWORD dwInitTimerElapse, //
	unsigned int one_level_scores,
	DOUBLE level_speedup_ratio,
	int boundary_x, int boundary_y,
	int init_x, int init_y, 
	int init_len,
	dirction init_dir)
{
	// 设置随机数种子
	// 需要使用随机数生成食物的位置等。
	FILETIME ft;
	GetSystemTimeAsFileTime(&ft);
	srand(ft.dwLowDateTime);

	dbLevelSpeedupRatio = level_speedup_ratio;
	dwTimerElapse = dwInitTimerElapse;
	dwOneLevelScores = one_level_scores;

	// 设置游戏的边界
	SetBoundary(boundary_x, boundary_y);

	// 创建表示贪吃蛇的数据结构
	CreateSnake(init_dir, init_x, init_y, init_len);

	// 创建表示食物的数据结构
	CreateFood();

	// 创建一个计时器
	// 每经过 dwTimerElapse 毫秒，hwnd窗口（主窗口）就会收到一个WM_TIMER消息。
	// 计时器是驱动本游戏进行的主要时间线。
	// dwTimerElapse变量影响游戏进行的快慢变化。
	SetTimer(hwnd, TIMER_ID, dwTimerElapse, NULL);

}