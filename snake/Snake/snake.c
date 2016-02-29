#include "snake.h"

#define INIT_LEN 5

GAME_COORD food;
PLIST snake_list;
dirction snake_dir;
int level_up_count;
int score = 0;
int level = 0;

// 判断两个位置GAME_COORD是否重合的函数
int CoordEqual(PGAME_COORD one, PGAME_COORD two)
{
	if (one->x == two->x && one->y == two->y)
		return 1;
	return 0;
}

dirction GetDirction()
{
	return snake_dir;
}

int GetScore()
{
	return score;
}

int GetLevel()
{
	return level;
}

PLIST GetSnakeList()
{
	return snake_list;
}

PGAME_COORD GetFood()
{
	return &food;
}

//改变方向、向前移动、变长、改变速度、吃到食物之后的动作。
void SetDirction(dirction dir)
{

	switch (snake_dir)
	{
	case SNAKE_UP:
		if (dir == SNAKE_DOWN)
			return;
		break;
	case SNAKE_DOWN:
		if (dir == SNAKE_UP)
			return;
		break;
	case SNAKE_LEFT:
		if (dir == SNAKE_RIGHT)
			return;
		break;
	case SNAKE_RIGHT:
		if (dir == SNAKE_LEFT)
			return;
		break;
	}
	snake_dir = dir;
}

// 蛇生长
int SnakeGorwup()
{
	PGAME_COORD pNewTail = (PGAME_COORD)malloc(sizeof(GAME_COORD));
	PGAME_COORD pTail;		// 倒数第一
	PGAME_COORD pLastButOne;	// 倒数第二
	int size = ListSize(snake_list);

	if (size >= CELLS_X*CELLS_Y-1) //长到最长了，游戏结束！~
		return SNAKE_COMPLETE;

	if (size == 0) // 没有头，不知从何生长，返回错误。
		return SNAKE_ERROR;

	if (size == 1) // 只有一个节点，按照当前方向生长。
	{
		pTail = (PGAME_COORD)ListGetAt(snake_list, 0/*只有一个节点，头就是尾*/);
		switch (snake_dir)
		{
		case SNAKE_LEFT:
			pNewTail->x = pTail->x + 1;
			pNewTail->y = pTail->y;
			break;
		case SNAKE_RIGHT:
			pNewTail->x = pTail->x - 1;
			pNewTail->y = pTail->y;
			break;
		case SNAKE_UP:
			pNewTail->x = pTail->x ;
			pNewTail->y = pTail->y + 1;
			break;
		case SNAKE_DOWN:
			pNewTail->x = pTail->x;
			pNewTail->y = pTail->y - 1;
			break;
		}

	}
	else // 有两个以上节点，取倒数第一和倒数第二计算生长方向。
	{
		pTail = (PGAME_COORD)ListGetAt(snake_list, size - 1);
		pLastButOne = (PGAME_COORD)ListGetAt(snake_list, size - 2);
		// 沿着倒数第二->倒数第一的方向，添加一个新的节点。
		pNewTail->x = pTail->x + (pTail->x - pLastButOne->x);
		pNewTail->y = pTail->y + (pTail->y - pLastButOne->y);

	}

	ListPushBack(snake_list, pNewTail);
	if ((size + 1) % level_up_count == 0)
	{
		level++;
		return SNAKE_LEVELUP;
	}
	return SNAKE_GROWUP;

}


// 创建一个食物
int CreateFood()
{
	PGAME_COORD posbody;
	int i;
	int size = ListSize(snake_list);

new_food:

	food.x = rand() % CELLS_X;
	food.y = rand() % CELLS_Y;

	// 判断是否和蛇重叠了。

	for (i = 0; i < size; i++)
	{
		posbody = (PGAME_COORD)ListGetAt(snake_list, i);
		if (CoordEqual(posbody, &(food)))
		{
			goto new_food;
		}
	}
	return 1;

}

// 创建蛇
int CreateSnake(dirction dir, int head_x, int head_y, int level_up, int init_len)
{
	PGAME_COORD p;

	SetDirction(dir);
	level_up_count = level_up;
	
	snake_list = ListCreate(NULL);

	p = (PGAME_COORD)malloc(sizeof(GAME_COORD));
	// 蛇头部的初始位置；
	p->x = head_x;
	p->y = head_y;
	ListPushFront(snake_list, p);

	for (int i = 1; i < init_len; i++)
	{
		//p = (PGAME_COORD)malloc(sizeof(GAME_COORD));
		SnakeGorwup();
	}
	return 1;
}


// 判断蛇是否死了。
// 返回0 蛇没有死 else 蛇死了。
int IsSnakeDead()
{
	PGAME_COORD posBody;
	PGAME_COORD posHead;

	int i;
	int size = ListSize(snake_list);


	// 判断是否死亡
	/// 判断是否碰到墙
	posHead = (PGAME_COORD)ListGetAt(snake_list, 0);

	if (posHead->x < 0 || posHead->x > CELLS_X ||
		posHead->y < 0 || posHead->y > CELLS_Y)
	{
		return SNAKE_DEAD;
	}
	/// 判断是否碰到自己
	//// 从第二个节点开始，逐一和头节点比较。
	size = ListSize(snake_list);

	for (i = 1; i < size; i++)
	{
		posBody = (PGAME_COORD)ListGetAt(snake_list, i);
		if (CoordEqual(posHead, posBody))
		{
			return SNAKE_DEAD;
		}
	}
	return SNAKE_MOVED;
}


// 用来将蛇移动一步，
// 移动以后
// 如果吃到了食物，则生长。
// 如果碰到了墙或者自己，则死亡，并返回是否死亡的状态。
int SnakeMove()
{
	// 完成移动的动作
	PGAME_COORD posHead;

	PGAME_COORD posTail;
	//int i;
	//int size = ListSize(snake_list);

	// 把蛇尾按照蛇的当前方向放置到蛇头。
	posHead = (PGAME_COORD)ListGetAt(snake_list, 0);
	posTail = (PGAME_COORD)ListPopBack(snake_list);

	// 根据当前蛇的方向来判断向那边移动
	switch (snake_dir)
	{
	case SNAKE_UP:
		posTail->y = posHead->y - 1;
		posTail->x = posHead->x;
		break;
	case SNAKE_DOWN:
		posTail->y = posHead->y + 1;
		posTail->x = posHead->x;
		break;
	case SNAKE_LEFT:
		posTail->x = posHead->x - 1;
		posTail->y = posHead->y;
		break;
	case SNAKE_RIGHT:
		posTail->x = posHead->x + 1;
		posTail->y = posHead->y;
		break;
	}
	ListPushFront(snake_list, posTail);

	// 判断是否吃到了食物
	if (CoordEqual(posHead, &food))
	{
		CreateFood();
		return SnakeGorwup();
	}

	return IsSnakeDead();
}