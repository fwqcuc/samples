## 一个古老游戏的新生——从贪吃蛇到编程入门。

我们这篇文章的贪吃蛇游戏，玩起来是这个样子的。

'配图'

对，就是一个非常正宗的贪吃蛇。

如果你把这篇文章读完，你发现写出贪吃蛇类似的游戏，像2048、扫雷、俄罗斯方块等等，其实很Easy的。

#### 先来看看难度。

这是一个**纯C语言**的代码，
'配图'

而且使用的是大多数计算专业本科的同学们最熟悉的编程环境**Visual Studio**，
'配图'

运行在最常用的Windows系统中。
'配图'

同学说，我们只会写出这样的程序：
'配图'

对于如何写贪吃蛇，完全懵了。

对的，它就是用的C语言，在Visual Studio。

耐心，继续读完。

#### 再来看看工作量。
这个游戏的源代码，一共没有超过**1400行**。
'配部分代码'
而且还是在注释异常丰富的情况下，
'配部分代码'
而且还是包括了一个链表的实现程序。
'配部分代码'
这是为了同学们能把代码看得跟明白，特意做了很多形式上的表现。我们在实际的工程开发中，代码可能写得更简洁一些，有信心在**600行**内完成同样的功能，这通常是一个成熟程序员**不超过一周**的工作量。（实际有人可能一天就写出来超过1000行代码）。


### 如何写？

跟着我的思路来。

1. 设计表示游戏状态的数据结构和数据。

计算机中，一切皆是数据。

贪吃蛇游戏，包括最基本的几个东西。**一条蛇**，**一个食物**以及**边界**。
更完整的描述是：一条蛇，在玩家的控制下改变移动方向，蛇自己爬行，“吃到”食物，会变长，同时不要碰到游戏边界和自己。

经过仔细的考虑和设计，需要以下数据就可以表示这个游戏：
* 食物的位置
* 蛇的移动方向
* 边界的大小。
* 蛇点的数量每一个点的位置

由于蛇会长的越来越长，而且各个点的位置会不断变化。所以**链表**是适合表示蛇的数据结构。这是整个程序中最复杂的数据结构了。

啊，链表，这是我大学生涯痛苦的经历。
难么？
码农界有一句名言，叫**不要重复发明轮子**。
所以像链表这样基础的东西，不需要自己去造，已经有很多人写过了很好的了。你不可能比他们写得更好了。
示例代码中的链表也不是自己写的！放在这里完全就是为了完整的演示。

链表的数据类型定义
```C
typedef struct _NODE
{
	void* data;
	struct _NODE* next;
}NODE, *PNODE;

typedef struct _LIST
{
 void* list_data;
 PNODE first;
}LIST, *PLIST;
```

虽然没有画出来，但是实际是有格子中。食物和蛇的每一个节点的位置都是格子中的。蛇一步爬行一个格子。
* 边界大小:X Y.
这些数据中，很多都是**坐标**，所以我们专门设计了一个**结构体**数据类型，来表示坐标类型的数据。
``` C
// 游戏坐标
typedef struct _GAME_COORD
{
	short x;
	short y;
}GAME_COORD, *PGAME_COORD;
```
然后我们还需要一些常量来表示方向，这里使用

```C
// 蛇的方向
typedef enum _dirction
{
	SNAKE_UP,
	SNAKE_DOWN,
	SNAKE_LEFT,
	SNAKE_RIGHT,
}dirction;
```

[关于typedef]
这是一个C语言的关键字，功能是将一个已有的数据类型**定义为**，或者理解为**重命名**为一个新的数据类型。
上面是将枚举类型[enum _dirction]和结构体类型[struct _GAME_COORD]，重命名为了一个比较方便记忆和输入的名字。以后的代码中就使用新的名称。
例如一个更简单的情况：
```C
typedef unsigned long       DWORD;
```

这些数据的类型都定义完成了，然后定义变量。

```C
/************* 全局变量 ****************/
// 食物
GAME_COORD food;
// 蛇（链表）
PLIST snake_list;
// 蛇移动方向
dirction snake_dir;
// 游戏边界（这是右下，左上为0,0）
GAME_COORD boundary;
```

* 蛇爬行的速度（每爬行一步间隔的时间）。
```C
// 计时器到时间隔
DWORD dwTimerElapse;
```

有了这些数据，似乎游戏就表示清楚了。但是我们还希望游戏可以**计分**和**升级**。那么需要
* 分数;
* 级别;
* 升级条件;采用积分每累计到一定的分数，就升级一次的方式。
* 每升级一次，游戏速度的变化。出于简单考虑，我们可以设计这个比例是固定的。

``` C
// 每提高一级，计时器时钟周期缩短的比例。
DOUBLE dbLevelSpeedupRatio;
// 此变量表示多少个积分上升一个级别
DWORD dwOneLevelScores;

// 保存计分，初始为0
int score = 0;
// 保存级别，初始为0
int level = 0;
```

以上这些数据，和界面的显示是无关的。比如有一些数据，我们没有在这里考虑，比如用来显示食物和蛇的圆圈的**颜色**、**大小**等等。因为这些内容*和游戏逻辑无关*，只在显示的时候用到了。

2. 接口和封装

4. 编写一些函数来操作这些数据。然后完成游戏逻辑功能的函数编写。

游戏的过程，就是这些数据变化的过程。所以在游戏过程中，程序会不断的去读和写这些数据。
下面就是老师设计的去读写这些数据的操作。

```CPP
/// snake_and_food.c中的接口函数

// 设置边界坐标
void SetBoundary(int x, int y);

// 获得边界坐标
PGAME_COORD GetBoundary();

// 生成新的食物。
int CreateFood();

// 获得食物的坐标。
PGAME_COORD GetFood();

// 创建蛇
void CreateSnake(dirction dir, int head_x, int head_y, int init_len);

// 销毁蛇，释放内存资源。
void DistroySnake();

// 用来移动一步，
// 移动以后，如果吃到了食物，则生长。
// 如果碰到了墙或者自己，则死亡，并返回是否死亡的状态。
int SnakeMove();

// 蛇生长
int SnakeGorwup();

// 获得蛇的长度
int GetSnakeSize();

// 获得蛇的第一个节点的坐标
PGAME_COORD GetSnakeHead();

// 获得蛇的最后一个节点的坐标
PGAME_COORD GetSnakeTail();

// 按照序号获得蛇的节点的坐标，不能超过蛇的长度，否则返回NULL
PGAME_COORD GetSnakeAt(int n);

// 改变蛇移动的方向
void SetDirction(dirction dir);

// 获得当前蛇的方向
dirction GetDirction();
```

以上，我们发所有对游戏数据结构的操作都定义为了函数，有了这些函数，上次的控制程序，调用就完成功能了，而不需要关心数据结构到是如何设计的。这是一种**分层的设计思想**。

以后我们还会常常听到一个词**封装**，也是这个意思。

那么是不是链表的使用并不需要了解链表具体是如何实现的，只需要知道链表可以有什么作用，如何使用。
为了尽量屏蔽掉实现细节，而便于其他人使用，链表的开发人员，需要编写出一系列对链表的操作函数，我们通常会把这种函数称为接口。
看看有了这些接口函数，我们还需要知道链表实现的每一个细节吗，我们只需要调用这些函数就可以了。

``` C
/***  创建一个新的链表  ***/
PLIST ListCreate(void* list_data);

/***  插入节点到链表   ***/
int ListInsertAt(PLIST list, unsigned int n, void* data);

/***  在链表头部插入节点   ***/
void ListPushFront(PLIST list, void* data);

/***  在链表尾部插入节点   ***/
void ListPushBack(PLIST list, void* data);

/***  删除链表头部节点   ***/
void* ListPopFront(PLIST list);

/***  删除链表尾部节点   ***/
void* ListPopBack(PLIST list);

/***  根据序号获得节点   ***/
void* ListGetAt(PLIST list, unsigned int n);

/***  根据序号删除节点   ***/
void* ListDeleteAt(PLIST list, int n);

/***  删除链表中的所有节点   ***/
void ListClearAndFree(PLIST list);

/***  删除整个链表   ***/
void ListDistory(PLIST list);

/***  删除整个链表，并链表中的全部释放   ***/
void ListDistoryAndFree(PLIST list);

/***  获得当前链表大小（节点数量）   ***/
int ListSize(PLIST list);
```
3. 启动和流程

* 数据结构的初始化过程

有了上面的那些数据和接口函数作为基础游戏的初始化过程比较容易的完成。

```CPP
// 游戏的初始化，
// 创建游戏的内部数据结构和系统对象。
void CreateGame(HWND hwnd, 
	DWORD dwInitTimerElapse, 
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
```

然后在程序以后，合适的地方，调用CreateGame这个函数：

```CPP
		CreateGame(hwnd, 
			INIT_TIMER_ELAPSE,
			ONE_LEVELS_SCORES,
			SPEEDUP_RATIO, 
			MAX_X, MAX_Y,
			INIT_X, INIT_Y,
			INIT_SNAKE_LEN,
			INIT_DIR);

```
调用CreateGame时，输入的参数都是以宏的方式定义的常量。

```CPP
// 游戏的参数的设置 
#define INIT_TIMER_ELAPSE	300	// 初始的时钟周期，确定游戏初始速度
#define	ONE_LEVELS_SCORES	5	// 每升级一次需要的计分
#define INIT_SNAKE_LEN		5	// 蛇的长度
#define SPEEDUP_RATIO		0.8 // 升级以后时间周期（确定游戏速度）提高的比例。
#define MAX_X		18	// 游戏界面大小
#define MAX_Y		20	// 游戏界面大小
#define INIT_X		3	// 蛇的初始位置
#define INIT_Y		3	// 蛇的初始位置
#define INIT_DIR	SNAKE_LEFT	// 蛇的初始方向
```

这么做的原因，是便于代码的阅读。同时如果以后想修改一下这些参数，让游戏变得快一些，界面大一些或者小一些，可以非常便捷。
这些基本就是程序的主要参数了。

* 入口函数

一个特别的地方，Windows系统中，图形用户界面的程序的入口函数的名称是WinMain，而不是标准c的main函数了。入口函数叫什么名字，只是约定而已。这个没有什么奇怪的，我们以后还会在不同的地方见到不同名称的入口函数。

现在我们只需要知道，在我们这个程序中，程序是从WinMain函数开始执行的。

** 关于Windows数据类型。

前面介绍了C语言关键字 typedef，Windows的接口函数中，使用了大量特有的，通过这种方式定义的类型。
```CPP
/********************************************************************************
* ##########关于Windows数据类型##########
*
* Windows在C语言的基础上定义了很多Windows特有的类型。都是通过C语言关键字typedef定义的。
* Windows类型都是全大写。
*
* DWORD LPSTR WPARAM LPARAM HWND等
* 其中，以'H'大头的数据类型都是句柄
*
*******************************************************************************/
```
例如Windows的头文件中有这样的内容：

```CPP
typedef unsigned long       DWORD;
typedef int                 BOOL;
typedef unsigned char       BYTE;
typedef unsigned short      WORD;
```

```CPP
typedef struct _SYSTEMTIME {
    WORD wYear;
    WORD wMonth;
    WORD wDayOfWeek;
    WORD wDay;
    WORD wHour;
    WORD wMinute;
    WORD wSecond;
    WORD wMilliseconds;
} SYSTEMTIME, *PSYSTEMTIME, *LPSYSTEMTIME;

```


** 关于API函数。

** 关于消息机制。



4. 显示出来

在界面上显示和绘图是单独的一门技术——GDI.

5. 让蛇动起来



* 初始化过程

* 定时移动一步
用到了操作系统的机制，计时器——Timer。


* 键盘控制蛇的方向

* 升级、加速。

### 还需要做什么？
5. 把代码串起来。


6. 我并不是按照我说的顺序写出来的代码


### 总结，为什么我们学了那么多编程语言，但是我们还是不会写代码。

一个重要原因是，'你放弃了'。

还有一个更重要的原因，是'其实你还没学完'。**知识体系**还不完整。学编程不等于学习程序语言。

而需要包括以下5个方面的学习：
* 编程语言；
* 开发工具；
* 接口和库；
* 运行机理；
* 设计模式；

而这个例子，5个方面都涉及到了。
