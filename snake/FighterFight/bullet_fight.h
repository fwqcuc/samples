typedef struct _BULLET
{
	unsigned int x;
	unsigned int y;
	double dir; // 移动时，x相对于y
	unsigned int y_step;
	unsigned int type;
	unsigned int power;
}BULLET, *LPBULLET;

#define BULLET_OUT	0
#define BULLET_HIT	1
#define BULLET_MOVE 2


LPBULLET CreateBullet(unsigned int x, unsigned int y);
void DestoryBullet(LPBULLET lpbullet);
int MoveBullet(LPBULLET lpbullet); 
unsigned int GetBulletX(LPBULLET lpbullet);
unsigned int GetBulletY(LPBULLET lpbullet);