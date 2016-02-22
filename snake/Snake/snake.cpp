#include "snake.h"

POSITION food;
list <POSITION> snake;
dirction snake_dir;

#define INIT_LEN 5

// 判断两个位置POSITION是否重合的函数
bool IsCoincide(POSITION one, POSITION two)
{ 
	if (one.x == two.x && one.y == two.y)
		return true;
	return false;
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

bool Gorwup()
{
	//POINT* posNewHead = new(POINT);
	POSITION posHead = snake.front();
	//snake.push_front(*posNewHead);
	switch (snake_dir)
	{
	case SNAKE_UP:
		posHead.y -= 1;
		break;
	case SNAKE_DOWN:
		posHead.y += 1;
		break;
	case SNAKE_LEFT:
		posHead.x -= 1;
		break;
	case SNAKE_RIGHT:
		posHead.x += 1;
		break;
	}
	snake.push_front(posHead);

	return true;
}




bool CreateFood()
{
	bool on_snake = false;

	while(true)
	{
		food.x = rand() % CELLS_X ;
		food.y = rand() % CELLS_Y ;

		// 判断是否和蛇重叠了。
		list <POSITION>::iterator posbody;
		for(posbody = snake.begin(); posbody != snake.end(); posbody++)
		{
			if(IsCoincide(*posbody,food))
			{
				on_snake = true;
				break;
			}
		}
		if(!on_snake)
			return true;
	}
}


bool CreateSnake()
{
	SetDirction(SNAKE_LEFT);

	POSITION p;
	snake.clear();
	p.x = 10 ; // 蛇的初始位置
	p.y = 10 ; // 蛇的初始位置
	for(int i = 0; i<INIT_LEN; i++)
	{
		p.x+=1;
		snake.push_back(p);
	}
	return true;
}

// 用来将蛇移动一步，
// 如果移动之后蛇没有死则返回0， 如果蛇死了（撞到墙或者撞到自己）则返回 -1；
int SnakeMove()
{
	// 完成移动的动作
	POSITION posHead;
	posHead = snake.front();
	// 根据当期蛇的方向来判断向那边移动
	switch (snake_dir)
	{
	case SNAKE_UP:
		posHead.y -= 1;
		break;
	case SNAKE_DOWN:
		posHead.y += 1;	
		break;
	case SNAKE_LEFT:
		posHead.x -= 1;
		break;
	case SNAKE_RIGHT:
		posHead.x += 1;
		break;
	}

	snake.push_front(posHead);
	snake.pop_back();


	// 判断是否吃到了食物
	if (IsCoincide(posHead,food ))
	{
		CreateFood();
		Gorwup();
		return 0;
	}

	// 判断是否死亡
	// 判断是否碰到自己
	list <POSITION>::iterator posbody;
	// 从第二个节点开始，逐一和头节点比较。
	for(posbody = snake.begin(), posbody++; posbody != snake.end (); posbody++)
	{
		if(IsCoincide(posHead, *posbody))
		{
			return -1;
		}

	}
	// 判断是否碰到墙
	if(posHead.x < 0 || posHead.x > CELLS_X  || 
		posHead.y < 0 || posHead.y > CELLS_Y )
	{
		return -1; 
	}

	return 0;
}