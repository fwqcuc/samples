#include "snake.h"

// 蛇、食物和蛇运行方向是全局唯一的变量。
POSITION food;
PLIST snake;
dirction snake_dir;

#define INIT_LEN 5

// 判断两个位置POSITION是否重合的函数
int IsCoincide(POSITION* one, POSITION* two)
{
	if (one->x == two->x && one->y == two->y)
		return 1;
	return 0;
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
int Gorwup()
{
	POSITION* pNewTail = (POSITION*)malloc(sizeof(POSITION));
	POSITION* pTail;		// 倒数第一
	POSITION* pLastButOne;	// 倒数第二
	int size = ListSize(snake);

	pTail = (POSITION*)ListGetAt(snake, size - 1);
	pLastButOne = (POSITION*)ListGetAt(snake, size - 2);
	// 沿着倒数第二->倒数第一的方向，添加一个新的节点。
	pNewTail->x = pTail->x + (pTail->x - pLastButOne->x);
	pNewTail->y = pTail->y + (pTail->y - pLastButOne->y);

	ListPushBack(snake, pNewTail);

	return 1;
}


// 创建一个食物
int CreateFood()
{
	POSITION* posbody;
	int i;
	int size = ListSize(snake);

new_food:

	food.x = rand() % CELLS_X;
	food.y = rand() % CELLS_Y;

	// 判断是否和蛇重叠了。

	for (i = 0; i < size; i++)
	{
		posbody = (POSITION*)ListGetAt(snake, i);
		if (IsCoincide(posbody, &food))
		{
			goto new_food;
		}
	}
	return 1;

}

// 创建蛇
int CreateSnake()
{
	SetDirction(SNAKE_LEFT);

	//POSITION h;
	POSITION* p;
	snake = ListCreate(NULL);

	for (int i = 0; i < INIT_LEN; i++)
	{
		p = (POSITION*)malloc(sizeof(POSITION));
		// 蛇的初始位置 10， 10；
		p->x = 10 + i;
		p->y = 10;
		ListPushBack(snake, p);
	}
	return 1;
}


// 判断蛇是否死了。
// 返回0 蛇没有死 else 蛇死了。
int IsSnakeDead()
{
	POSITION* posBody;
	POSITION* posHead;

	int i;
	int size = ListSize(snake);


	// 判断是否死亡
	/// 判断是否碰到墙
	posHead = (POSITION*)ListGetAt(snake, 0);

	if (posHead->x < 0 || posHead->x > CELLS_X ||
		posHead->y < 0 || posHead->y > CELLS_Y)
	{
		return -1;
	}
	/// 判断是否碰到自己
	//// 从第二个节点开始，逐一和头节点比较。
	size = ListSize(snake);

	for (i = 1; i < size; i++)
	{
		posBody = (POSITION*)ListGetAt(snake, i);
		if (IsCoincide(posHead, posBody))
		{
			return -1;
		}
	}
	return 0;
}


// 用来将蛇移动一步，
// 移动以后
// 如果吃到了食物，则生长。
// 如果碰到了墙或者自己，则死亡，并返回是否死亡的状态。
int SnakeMove()
{
	// 完成移动的动作
	POSITION* posHead;

	POSITION* posTail;
	//int i;
	//int size = ListSize(snake);

	// 把蛇尾按照蛇的当前方向放置到蛇头。
	posHead = (POSITION*)ListGetAt(snake, 0);
	posTail = (POSITION*)ListPopBack(snake);

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
	ListPushFront(snake, posTail);

	// 判断是否吃到了食物
	if (IsCoincide(posHead, &food))
	{
		CreateFood();
		Gorwup();
		return 0;
	}

	return IsSnakeDead();
}