#include "auto_fly.h"
#include "LinkList.h"
#include <time.h>

PLIST list_flys;

int flys_init()
{
	time_t t;
	list_flys = ListCreate(0);
	srand((unsigned int)(time(&t)*time(&t)));
	return 0;
}

LPAUTO_FLY create_fly(
	FLY_TYPE type,
	int x,
	int y,
	double dir,		// 移动时，x相对于y
	int y_step,	// y方向每个时间周期移动的距离
	//FLY_STATE state,
	unsigned int power,
	int ratio_x,		// 在这个范围内击中都有效。
	int ratio_y		// 在这个范围内击中都有效。
	)
{
	LPAUTO_FLY auto_fly = malloc(sizeof(AUTO_FLY));
	if (auto_fly == 0)
		return (LPAUTO_FLY)0;
	auto_fly->x = x;
	auto_fly->y = y;
	auto_fly->dir = dir;
	auto_fly->power = power;
	auto_fly->type = type;
	auto_fly->y_step = y_step;
	auto_fly->state = FLY_MOVED;
	auto_fly->ratio_x = ratio_x;
	auto_fly->ratio_y = ratio_y;

	ListPushBack(list_flys, auto_fly);

	return auto_fly;
}

void flys_destory()
{
	ListClearAndFree(list_flys);
	list_flys = 0;
}



void destory_fly_at(unsigned int i)
{
	LPAUTO_FLY fly = ListDeleteAt(list_flys, i);
	free(fly);
}

unsigned int get_flys_num()
{
	return ListSize(list_flys);
}

LPAUTO_FLY get_fly_at(unsigned int i)
{
	return (LPAUTO_FLY)ListGetAt(list_flys, i);
}


void fly_move(LPAUTO_FLY auto_fly)
{
	if (auto_fly->type == FLY_TYPE_BULLET)
		auto_fly->y -= auto_fly->y_step;
	else if (auto_fly->type == FLY_TYPE_ENEMY)
		auto_fly->y += auto_fly->y_step;
	auto_fly->x -= (int)(auto_fly->y_step*auto_fly->dir);
}

unsigned int get_fly_x(LPAUTO_FLY auto_fly)
{
	return auto_fly->x;
}

unsigned int get_fly_y(LPAUTO_FLY auto_fly)
{
	return auto_fly->y;
}

void fly_be_hit(LPAUTO_FLY auto_fly)
{
	auto_fly->state = FLY_HIT;
}

void fly_out(LPAUTO_FLY auto_fly)
{
	auto_fly->state = FLY_OUT;
}


// 判断是否被集中，
// 如果击中返回子弹的指针，否则返回空指针。
int be_hit(LPAUTO_FLY enemy, LPAUTO_FLY bullet)
{

	if (enemy->x + enemy->ratio_x > bullet->x &&
		enemy->x - enemy->ratio_x < bullet->x &&
		enemy->y + enemy->ratio_y > bullet->y &&
		enemy->y - enemy->ratio_y < bullet->y)
	{
		fly_be_hit(enemy);
		fly_be_hit(bullet);
		return 1;
	}
	else
	{
		// 只能从 FLY_MOVED 变为 FLY_HIT, 不能反向变化。
		return 0;
	}
}

void flys_move_step()
{
	unsigned int num, i, j;
	LPAUTO_FLY auto_fly, auto_fly_for_hit;
	num = get_flys_num();
	// 移动，并判断是否飞出。
	for (i = 0; i < num; i++)
	{
		auto_fly = get_fly_at(i);
		fly_move(auto_fly);
		if (get_fly_x(auto_fly) < 0 || get_fly_x(auto_fly) > MAX_X ||
			get_fly_y(auto_fly) < 0 || get_fly_y(auto_fly) > MAX_Y)
		{
			fly_out(auto_fly);
		}
	}
	// 逐个判断是否击中，标记状态。
	for (i = 0; i < num; i++)
	{
		auto_fly = get_fly_at(i);
		if (auto_fly->type == FLY_TYPE_ENEMY)
		{
			// 判断链表中所有子弹是否击中。
			for (j = 0; j < num; j++)
			{
				auto_fly_for_hit = get_fly_at(j);
				if (auto_fly_for_hit->type == FLY_TYPE_BULLET)
				{
					// 判断并标记
					be_hit(auto_fly, auto_fly_for_hit);
				}
			}
		}
	}
}


void destory_fly_by_state()
{
	unsigned int num, i;
	LPAUTO_FLY auto_fly;

again:
	num = get_flys_num();

	// 从后往前删，不然一次循环删除多个的话，就会超
	// 或者一次循环只删除一个，多次循环。
	// 这是链表可以改接的地方
	for (i = 0; i < num; i++)
	{
		auto_fly = get_fly_at(i);
		if (auto_fly->state == FLY_HIT)
		{
			destory_fly_at(i);
			goto again;
		}
		else if (auto_fly->state == FLY_OUT)
		{

			destory_fly_at(i);
			goto again;

		}
	}
}
