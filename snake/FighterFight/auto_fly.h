#include <Windows.h>

#ifndef _AUTO_FLY_H
#define _AUTO_FLY_H

#define MAX_X 500
#define MAX_Y 800

typedef enum _FLY_STATE
{
	FLY_OUT,
	FLY_HIT,
	FLY_MOVED,
}FLY_STATE;

typedef enum _FLY_TYPE
{
	FLY_TYPE_BULLET,
	FLY_TYPE_ENEMY,
	FLY_TYPE_MONEY,
}FLY_TYPE;

typedef struct _AUTO_FLY
{
	FLY_TYPE type;
	int x;
	int y;
	double dir;				// 移动时，x相对于y
	int y_step;				// y方向每个时间周期移动的距离
	FLY_STATE state;
	unsigned int power;
	int ratio_x;	// 在这个范围内击中都有效。
	int ratio_y;	// 在这个范围内击中都有效。
	
}AUTO_FLY, *LPAUTO_FLY;


#define RAND_DIR ((double)(rand()*2-RAND_MAX))/(RAND_MAX*5)

#define gen_bullet(x, y)	create_fly(FLY_TYPE_BULLET,	x, y, RAND_DIR, rand()%10+5, 0, 0, 0)
#define gen_enemy()			create_fly(FLY_TYPE_ENEMY, rand()%MAX_X, 0, 0, 3, 0, 10, 10)

int flys_init();
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
	);
void flys_destory();

void destory_fly_at(unsigned int i);

unsigned int get_flys_num();
LPAUTO_FLY get_fly_at(unsigned int i);


void fly_move(LPAUTO_FLY auto_fly);

unsigned int get_fly_x(LPAUTO_FLY auto_fly);

unsigned int get_fly_y(LPAUTO_FLY auto_fly);

void fly_out(LPAUTO_FLY auto_fly);
void flys_move_step();
void destory_fly_by_state();

#endif