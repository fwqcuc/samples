/********************************************************************************
* ##########  谈谈封装 ##########
* “封装”是程序不会乱掉的一个重要技能。
* 我们要写出结构化、易于阅读、理解和维护的代码。采用封装是比较容易掌握的方法。
* 
* 具体而言：
* 
* 1、先考虑好这个程序的逻辑和状态需要多少数据来表示，
* 比如这个贪吃蛇游戏，我们使用这些数据就可以表示全部游戏状态。
* // 食物
* GAME_COORD food;
* // 蛇（链表）
* PLIST snake_list;
* // 蛇移动方向
* dirction snake_dir;
* // 游戏边界（这是右下，左上为0,0）
* GAME_COORD boundary;
* 
* 2、写出一系列接口函数来操作这些数据。所谓接口函数，满足一下几个特征：
* (1) 这些数据除了接口函数以外，其他代码都不会直接访问。
* (2) 所有其他代码都只能通过调用这些接口函数来改变程序的状态，而不要直接去访问数据。
* 如本文件的若干函数都是对上述数据的操作。

* 这样实现了：对于上层代码，并不需要知道数据的操作逻辑，也不需要知道数据结构，而只需要调用函数即可。
* 对上次代码而言，逻辑简单了很多。
* 同样，如果数据结构和内部逻辑有了修改，那么可以做到接口函数的原型不变，
* 上层代码不变，而只需要修改接口函数的内部实现过程即可。
* 
* 这就称之为“封装”，或者称之为 “数据的封装和接口化”
*
*******************************************************************************/



/************** 头文件 ****************/
#include "snake.h"

/************* 全局变量 ****************/
// 食物
GAME_COORD food;
// 蛇（链表）
PLIST snake_list;
// 蛇移动方向
dirction snake_dir;
// 游戏边界（这是右下，左上为0,0）
GAME_COORD boundary;

/*********** 内部函数申明 **************/
/// 判断两个坐标是否相等。
int CoordEqual(PGAME_COORD one, PGAME_COORD two);
/// 判断蛇是否已死
int IsSnakeDead();

/**************函数定义****************/


// 判断两个坐标 GAME_COORD 是否重合
int CoordEqual(PGAME_COORD one, PGAME_COORD two)
{
	if (one->x == two->x && one->y == two->y)
		return 1;
	return 0;
}

// 设置边界坐标
void SetBoundary(int x, int y)
{
	boundary.x = x;
	boundary.y = y;
}

// 获得边界坐标
PGAME_COORD GetBoundary()
{
	return &boundary;
}

// 生成新的食物。
int CreateFood()
{
	PGAME_COORD posbody;
	int i;
	int size = ListSize(snake_list);

new_food:

	// 随机生成食物的坐标。
	food.x = rand() % boundary.x;
	food.y = rand() % boundary.y;

	// 判断是否和蛇重叠了，否则重新生成食物坐标，知道不重叠。

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

// 获得食物的坐标。
PGAME_COORD GetFood()
{
	return &food;
}

// 创建蛇
void CreateSnake(dirction dir, int head_x, int head_y, int init_len)
{
	PGAME_COORD p;
	int i;

	SetDirction(dir);

	snake_list = ListCreate(NULL);

	p = (PGAME_COORD)malloc(sizeof(GAME_COORD));
	// 蛇头部的初始位置；
	p->x = head_x;
	p->y = head_y;
	ListPushFront(snake_list, p);

	for (i = 1; i < init_len; i++)
	{
		//p = (PGAME_COORD)malloc(sizeof(GAME_COORD));
		SnakeGorwup();
	}
	return;
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

	if (posHead->x < 0 || posHead->x > boundary.x ||
		posHead->y < 0 || posHead->y > boundary.y)
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

// 销毁蛇，释放内存资源。
void DistroySnake()
{
	ListDistoryAndFree(snake_list);
	return;
}

// 用来移动一步，
// 移动以后，如果吃到了食物，则生长。
// 如果碰到了墙或者自己，则死亡，并返回是否死亡的状态。
int SnakeMove()
{
	// 头和尾的坐标
	PGAME_COORD posHead;
	PGAME_COORD posTail;

	// 把尾从链表中取出，按照当前方向放置到头的位置。
	posHead = (PGAME_COORD)ListGetAt(snake_list, 0);
	posTail = (PGAME_COORD)ListPopBack(snake_list);

	// 根据当前方向来设定新的头坐标。
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
		return SNAKE_EATEN_FOOD;
	}

	// 如果没有吃到食物判断是否撞到障碍，然后返回状态。
	return IsSnakeDead();
}

// 蛇生长
int SnakeGorwup()
{
	// 给新的节点分配内存
	PGAME_COORD pNewTail;
	PGAME_COORD pTail;		// 倒数第一节点
	PGAME_COORD pLastButOne;	// 倒数第二节点
	int size = GetSnakeSize();

	if (size >= boundary.x*boundary.y-1) //长到最长了，游戏结束！~
		return SNAKE_COMPLETE;

	if (size == 0) // 没有头，不知从何生长，返回错误。
		return SNAKE_ERROR;

	pNewTail = (PGAME_COORD)malloc(sizeof(GAME_COORD));
	if (size == 1) // 只有一个节点，按照当前的移动方向生长。
	{
		
		pTail = (PGAME_COORD)GetSnakeTail();
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
		pTail = (PGAME_COORD)GetSnakeTail();
		pLastButOne = (PGAME_COORD)GetSnakeAt(size - 2);
		// 沿着倒数第二->倒数第一的方向，添加一个新的节点。
		pNewTail->x = pTail->x + (pTail->x - pLastButOne->x);
		pNewTail->y = pTail->y + (pTail->y - pLastButOne->y);

	}

	// 新节点放入到蛇尾的位置
	ListPushBack(snake_list, pNewTail);
	return SNAKE_GROWUP;

}

// 获得蛇的长度
int GetSnakeSize()
{
	return ListSize(snake_list);
}

// 获得蛇的第一个节点的坐标
PGAME_COORD GetSnakeHead()
{
	return (PGAME_COORD)ListGetAt(snake_list, 0);
}

// 获得蛇的最后一个节点的坐标
PGAME_COORD GetSnakeTail()
{
	return (PGAME_COORD)ListGetAt(snake_list, GetSnakeSize() - 1);
}

// 按照序号获得蛇的节点的坐标，不能超过蛇的长度，否则返回NULL
PGAME_COORD GetSnakeAt(int n)
{
	if (n < ListSize(snake_list))
		return (PGAME_COORD)ListGetAt(snake_list, n);
	else
		return NULL;

}

// 改变蛇移动的方向
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


// 获得当前蛇的方向
dirction GetDirction()
{
	return snake_dir;
}