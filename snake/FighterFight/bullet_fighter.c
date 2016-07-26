#include "bullet_fight.h"
#include "LinkList.h"

PLIST list_bullets;
PLIST list_fights;

int InitBulletsAndFights()
{
	list_bullets = ListCreate(0);
	list_fights = ListCreate(0);
	return 0;
}

int DestoryAllBulletAndFights()
{
	ListClearAndFree(list_bullets);
	ListClearAndFree(list_fights);
	list_bullets = 0;
	list_fights = 0;
	return 0;
}

int NewBullet(unsigned int x, unsigned int y)
{
	LPBULLET lpNewBullet = CreateBullet(x, y);
	ListPushBack(list_bullets, lpNewBullet);
	return 0;
}

unsigned int GetBulletsNum()
{
	return ListSize(list_bullets);
}

LPBULLET GetBulletAt(unsigned int i)
{
	return (LPBULLET)ListGetAt(list_bullets, i);
}

LPBULLET CreateBullet(unsigned int x, unsigned int y)
{
	LPBULLET lpbullet = malloc(sizeof(BULLET));
	if (lpbullet == 0)
		return (LPBULLET)0;
	lpbullet->x = x;
	lpbullet->y = y;
	lpbullet->dir = 0;
	lpbullet->power = 0;
	lpbullet->type = 0;
	lpbullet->y_step = 5;
	return lpbullet;
}

void DestoryBullet(LPBULLET lpbullet)
{
	if(lpbullet!=0) free(lpbullet);
}

int MoveBullet(LPBULLET lpbullet)
{
	lpbullet->y -= lpbullet->y_step;
	lpbullet->x -= lpbullet->y_step*lpbullet->dir;
	if (lpbullet->y<0 || lpbullet->x<0)
	{
		return BULLET_OUT;
	}
	return BULLET_MOVE;
}

unsigned int GetBulletX(LPBULLET lpbullet)
{
	return lpbullet->x;
}

unsigned int GetBulletY(LPBULLET lpbullet)
{
	return lpbullet->y;
}