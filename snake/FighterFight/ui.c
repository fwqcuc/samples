#include <Windows.h>
#include "auto_fly.h"
#include "ui.h"

#pragma comment (lib, "Winmm.lib")

#define CLASS_NAME_BK		"bk_class"
#define CLASS_NAME_FIGHT	"fight_class"
#define CLASS_NAME_FLYS		"flys_class"

#define BITMAP_FILE_BK		"sky.bmp"

#define TIMER_ID			12340
#define TRANS_BK_COLOR		RGB(255,255,255)
#define FIGHTER_HEIGHT		50
#define FIGHTER_WIDTH		50


#define FIGHTER_MOVE_STEP	5		// 飞机在方向键的作用下，每次移动的像素；

#define GAME_HEIGHT 1000
#define GAME_WIDTH	500



HINSTANCE hinst;

HWND hwndFighter;
HWND hwndAutoflys;
HWND hwndBackground;

HBITMAP hbmpFighter;
HBITMAP hbmpBackground;
DWORD dwTimerElapse = 100;

LONG CALLBACK BackGroundWindowProc(
	HWND hwnd, //
	UINT msg, // 消息
	WPARAM wParam, // 消息参数，不同的消息有不同的意义，详见MSDN中每个消息的文档
	LPARAM lParam) // 消息参数，不同的消息有不同的意义，详见MSDN中每个消息的文档
{

	// 注意，是switch-case, 每次这个函数被调用，只会落入到一个case中。
	switch (msg)
	{
		// 当窗口被创建时，收到的第一个消息就是WM_CREATE，
		// 一般收到这个消息处理过程中，可以用来进行一些初始化的工作
	case WM_CREATE:
		BackgroundCreate(hwnd);
		break;

		// 当系统认为窗口上的GDI对象应该被重绘时，会向窗口发送一个WM_PAINT消息。
		// 当然应用程序也可以通过调用 UpateWindow来主动向窗口发送一个WM_PAINT消息。
		// 所有使用GDI在窗口上绘制图形的程序都 “必须” 写在这里。
		// 如果不是在WM_PAINT消息的处理过程中绘制GDI图形，那么在窗口刷新时就会被新被抹除和覆盖
	case WM_PAINT:
		BackgroundPaint(hwnd);
		break;

	case WM_MOVING:
		BackgroundResizeAndMove(hwnd, (LPRECT)lParam);
		break;

	case WM_SIZE:
	{
		RECT rectNew;
		GetWindowRect(hwnd, &rectNew);
		BackgroundResizeAndMove(hwnd, &rectNew);
		break;
	}
	case WM_KEYDOWN:
		//OnKeyDown(hwnd, (UINT)wParam);
		break;

	case WM_LBUTTONDOWN:
		break;

	case WM_TIMER:
		break;

	case WM_DESTROY:
		ExitProcess(0);
		break;

	default:
		break;
	}
	return DefWindowProc(hwnd,
		msg,
		wParam,
		lParam);
}



BOOL BackGroundWindwowRegister(HINSTANCE hinstance)
{
	WNDCLASS wc;
	// 窗口句柄，hwnd变量是主窗口的句柄，这个程序中只用到了一个窗口。

	// Fill in the window class structure with parameters 
	// that describe the main window. 

	// 窗口类的样式，这里设置的样式表示窗口在大小变化是需要重绘
	wc.style = CS_HREDRAW | CS_VREDRAW;
	// 一个函数指针，这个函数用来处理窗口消息。 详见 MainWndProc函数的注释。
	wc.lpfnWndProc = BackGroundWindowProc;
	// no extra class memory 
	wc.cbClsExtra = 0;
	// no extra window memory
	wc.cbWndExtra = 0;
	// handle to instance 
	wc.hInstance = hinstance;
	// hIcon成员用来指定窗口的图标
	// 这里直接使用LoadIcon函数加载了一个系统预定义的图标，开发人员可也可以自己创建图标。
	wc.hIcon = NULL;
	// Cursor是鼠标光标，这里是设定了鼠标光标的样式。
	// 直接使用LoadCursor API函数载入了一个系统预定义的光标样式，还有IDC_CROSS,IDC_HAND等样式 
	wc.hCursor = LoadCursor(NULL,
		IDC_CROSS);
	// GetStockObject的功能是加载一个系统预定义（在栈中）的GDI对象，
	// 这里加载的是一个白色的画刷，有关画刷和GDI对象，详见GDI说明。
	wc.hbrBackground = (HBRUSH)GetStockObject(
		WHITE_BRUSH);
	// 窗口的菜单的资源名。
	wc.lpszMenuName = NULL;
	// 给窗口类起一个名字，在创建窗口时需要这个名字。
	wc.lpszClassName = CLASS_NAME_BK;

	// Register the window class. 

	if (!RegisterClass(&wc))
	{
		// 窗口注册失败，消息框提示，并退出。
		MessageBox(NULL, "创建窗口class失败", "错误！", MB_ICONERROR | MB_OK);
		return FALSE;
	}
	// 窗口注册成功，继续运行。
	return TRUE;
}

HWND BackgroundWindowCreate(HINSTANCE hinstance)
{

	// Create the main window. 
	HWND hwnd;
	hwnd = CreateWindowEx(
		0,
		CLASS_NAME_BK,			// 窗口类名，必须是已经注册了的窗口类
		"",		// title-bar string 
		WS_OVERLAPPEDWINDOW,	// 窗口的style，这个表示为top-level window 
		CW_USEDEFAULT,			// 窗口水平位置default horizontal POINT 
		CW_USEDEFAULT,			// 窗口垂直位置default vertical POINT 
		CW_USEDEFAULT,			// 窗口宽度 default width 
		CW_USEDEFAULT,			// 窗口高度 default height 
		(HWND)NULL,				// 父窗口句柄 no owner window 
		(HMENU)NULL,			// 窗口菜单的句柄 use class menu 
		hinstance,				// 应用程序实例句柄 handle to application instance 
		(LPVOID)NULL);			// 指向附加数据的指针 no window-creation data 

	if (!hwnd)
	{
		// 窗口创建失败，消息框提示，并退出。
		MessageBox(NULL, "创建窗口失败", "错误！", MB_ICONERROR | MB_OK);
		return NULL;
	}

	// 窗口创建成功，继续运行。

	// 显示窗口，WinMain函数的nCmdShow参数在这里发挥作用，一般都设置为SW_SHOW
	ShowWindow(hwnd, SW_SHOW);

	// 刷新窗口，向窗口发送一个WM_PAINT消息，使得窗口进行重绘。
	UpdateWindow(hwnd);
	return hwnd;

}

LONG CALLBACK FighterWindowProc(
	HWND hwnd, //
	UINT msg, // 消息
	WPARAM wParam, // 消息参数，不同的消息有不同的意义，详见MSDN中每个消息的文档
	LPARAM lParam) // 消息参数，不同的消息有不同的意义，详见MSDN中每个消息的文档
{
	HDC hdc, hdcMem;
	PAINTSTRUCT ps;
	RECT rect;
	// 注意，是switch-case, 每次这个函数被调用，只会落入到一个case中。
	switch (msg)
	{
		// 当窗口被创建时，收到的第一个消息就是WM_CREATE，
		// 一般收到这个消息处理过程中，可以用来进行一些初始化的工作
	case WM_CREATE:
		break;

		// 当系统认为窗口上的GDI对象应该被重绘时，会向窗口发送一个WM_PAINT消息。
		// 当然应用程序也可以通过调用 UpateWindow来主动向窗口发送一个WM_PAINT消息。
		// 所有使用GDI在窗口上绘制图形的程序都 “必须” 写在这里。
		// 如果不是在WM_PAINT消息的处理过程中绘制GDI图形，那么在窗口刷新时就会被新被抹除和覆盖
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		// Create a memory device compatible with the above DC variable
		hdcMem = CreateCompatibleDC(hdc);
		// Select the new bitmap
		SelectObject(hdcMem, hbmpFighter);
		GetClientRect(hwnd, &rect);
		//// Copy the bits from the memory DC into the current dc
		StretchBlt(hdc,
			rect.left,
			rect.top,
			rect.right - rect.left,
			rect.bottom - rect.top,
			hdcMem,
			0, 0, 1024, 1024,
			SRCCOPY);
		//GetClientRect(hwnd, &rect);
		//StretchBlt(hdc, 0, 0, rect.right, rect.bottom,
		//	hdcMem, 0, 0, 1024, 1024, SRCCOPY);
		// Restore the old bitmap
		DeleteDC(hdcMem);
		EndPaint(hwnd, &ps);
		break;

	case WM_KEYDOWN:
		FighterKeyDown(hwnd, (UINT)wParam);
		break;

	case WM_LBUTTONDOWN:
		break;

	case WM_TIMER:
		break;

	case WM_DESTROY:
		ExitProcess(0);
		break;

	default:
		break;
	}
	return DefWindowProc(hwnd,
		msg,
		wParam,
		lParam);
}


HWND FighterWindowCreate(HINSTANCE hinstance)
{
	HWND hwnd;
	hwnd = CreateWindowEx(
		WS_EX_LAYERED | WS_EX_TOPMOST | WS_EX_NOACTIVATE,
		CLASS_NAME_FIGHT,			// 窗口类名，必须是已经注册了的窗口类
		"",			// title-bar string 
		WS_POPUP,	// 窗口的style，这个表示为top-level window 
		CW_USEDEFAULT,			// 窗口水平位置default horizontal POINT 
		CW_USEDEFAULT,			// 窗口垂直位置default vertical POINT 
		CW_USEDEFAULT,			// 窗口宽度 default width 
		CW_USEDEFAULT,			// 窗口高度 default height 
		(HWND)NULL,				// 父窗口句柄 no owner window 
		(HMENU)NULL,			// 窗口菜单的句柄 use class menu 
		hinstance,				// 应用程序实例句柄 handle to application instance 
		(LPVOID)NULL);			// 指向附加数据的指针 no window-creation data 
	if (!hwnd)
	{
		GetLastError();
		// 窗口创建失败，消息框提示，并退出。
		MessageBox(NULL, "创建窗口失败", "错误！", MB_ICONERROR | MB_OK);
		return NULL;
	}


	if (!SetLayeredWindowAttributes(
		hwnd, TRANS_BK_COLOR,
		255, LWA_COLORKEY | LWA_ALPHA))
	{
		DWORD dwError = GetLastError();
	}

	// 窗口创建成功，继续运行。
	// 显示窗口，WinMain函数的nCmdShow参数在这里发挥作用，一般都设置为SW_SHOW
	ShowWindow(hwnd, SW_SHOW);
	// 刷新窗口，向窗口发送一个WM_PAINT消息，使得窗口进行重绘。
	UpdateWindow(hwnd);
	return hwnd;
}

BOOL FighterWindowRegister(HINSTANCE hinstance)
{
	WNDCLASS wc;
	// 窗口句柄，hwnd变量是主窗口的句柄，这个程序中只用到了一个窗口。

	// Fill in the window class structure with parameters 
	// that describe the main window. 
	// 窗口类的样式，这里设置的样式表示窗口在大小变化是需要重绘
	wc.style = CS_HREDRAW | CS_VREDRAW;
	// 一个函数指针，这个函数用来处理窗口消息。 详见 MainWndProc函数的注释。
	wc.lpfnWndProc = FighterWindowProc;
	// no extra class memory 
	wc.cbClsExtra = 0;
	// no extra window memory
	wc.cbWndExtra = 0;
	// handle to instance 
	wc.hInstance = hinstance;
	// hIcon成员用来指定窗口的图标
	// 这里直接使用LoadIcon函数加载了一个系统预定义的图标，开发人员可也可以自己创建图标。
	wc.hIcon = NULL;
	// Cursor是鼠标光标，这里是设定了鼠标光标的样式。
	// 直接使用LoadCursor API函数载入了一个系统预定义的光标样式，还有IDC_CROSS,IDC_HAND等样式 
	wc.hCursor = LoadCursor(NULL, IDC_CROSS);
	// GetStockObject的功能是加载一个系统预定义（在栈中）的GDI对象，
	// 这里加载的是一个白色的画刷，有关画刷和GDI对象，详见GDI说明。
	wc.hbrBackground = (HBRUSH)CreateSolidBrush(TRANS_BK_COLOR);
	// 窗口的菜单的资源名。
	wc.lpszMenuName = NULL;
	// 给窗口类起一个名字，在创建窗口时需要这个名字。
	wc.lpszClassName = CLASS_NAME_FIGHT;
	// Register the window class. 

	if (!RegisterClass(&wc))
	{
		// 窗口注册失败，消息框提示，并退出。
		MessageBox(NULL, "创建窗口class失败", "错误！", MB_ICONERROR | MB_OK);
		return FALSE;
	}
	return TRUE;
}


LONG AutoflysPaint(HWND hwnd)
{
	HDC hdc, hdcMem;
	//PAINTSTRUCT ps;
	RECT rect;

	unsigned int i;
	HBITMAP hbmMem;
	BITMAP bmp;

	hdc = GetDC(hwnd);
	GetClientRect(hwnd, &rect);
	// Create a memory device compatible with the above DC variable
	hdcMem = CreateCompatibleDC(hdc);

	SelectObject(hdcMem, hbmpBackground);

	GetObject(hbmpBackground, sizeof(BITMAP), &bmp);

	StretchBlt(hdc,
		rect.left, rect.top,
		rect.right - rect.left, rect.bottom - rect.top,
		hdcMem,
		0, 0,
		bmp.bmWidth, bmp.bmHeight,
		SRCCOPY);

	DeleteObject(hdcMem);
	DeleteDC(hdcMem);
	ReleaseDC(hwnd, hdc);
	DeleteDC(hdc);
	return 0;
}

LONG CALLBACK AutoflyWindowProc(HWND hwnd, UINT msg, WPARAM wParam,LPARAM lParam)
{
	//PAINTSTRUCT ps;
	//RECT rect;
	// 注意，是switch-case, 每次这个函数被调用，只会落入到一个case中。
	switch (msg)
	{
		// 当窗口被创建时，收到的第一个消息就是WM_CREATE，
		// 一般收到这个消息处理过程中，可以用来进行一些初始化的工作
	case WM_CREATE:
		AutoflysCreate(hwnd);
		break;

		// 当系统认为窗口上的GDI对象应该被重绘时，会向窗口发送一个WM_PAINT消息。
		// 当然应用程序也可以通过调用 UpateWindow来主动向窗口发送一个WM_PAINT消息。
		// 所有使用GDI在窗口上绘制图形的程序都 “必须” 写在这里。
		// 如果不是在WM_PAINT消息的处理过程中绘制GDI图形，那么在窗口刷新时就会被新被抹除和覆盖
	case WM_PAINT:
		AutoflysPaint(hwnd);
		break;

	case WM_KEYDOWN:
		break;

	case WM_LBUTTONDOWN:
		break;

	case WM_TIMER:
		break;

	case WM_DESTROY:
		ExitProcess(0);
		break;

	default:
		break;
	}
	return DefWindowProc(hwnd,
		msg,
		wParam,
		lParam);
}


HWND AutoflyWindowCreate(HINSTANCE hinstance)
{
	HWND hwnd;
	hwnd = CreateWindowEx(
		WS_EX_LAYERED | WS_EX_TOPMOST | WS_EX_NOACTIVATE,
		CLASS_NAME_FLYS,			// 窗口类名，必须是已经注册了的窗口类
		"",			// title-bar string 
		WS_POPUP,	// 窗口的style，这个表示为top-level window 
		CW_USEDEFAULT,			// 窗口水平位置default horizontal POINT 
		CW_USEDEFAULT,			// 窗口垂直位置default vertical POINT 
		CW_USEDEFAULT,			// 窗口宽度 default width 
		CW_USEDEFAULT,			// 窗口高度 default height 
		(HWND)NULL,				// 父窗口句柄 no owner window 
		(HMENU)NULL,			// 窗口菜单的句柄 use class menu 
		hinstance,				// 应用程序实例句柄 handle to application instance 
		(LPVOID)NULL);			// 指向附加数据的指针 no window-creation data 
	if (!hwnd)
	{
		GetLastError();
		// 窗口创建失败，消息框提示，并退出。
		MessageBox(NULL, "创建窗口失败", "错误！", MB_ICONERROR | MB_OK);
		return NULL;
	}

	if (!SetLayeredWindowAttributes(
		hwnd, TRANS_BK_COLOR,
		255, LWA_COLORKEY | LWA_ALPHA))
	{
		DWORD dwError = GetLastError();
	}

	// 窗口创建成功，继续运行。
	// 显示窗口，WinMain函数的nCmdShow参数在这里发挥作用，一般都设置为SW_SHOW
	ShowWindow(hwnd, SW_SHOW);
	// 刷新窗口，向窗口发送一个WM_PAINT消息，使得窗口进行重绘。
	UpdateWindow(hwnd);
	return hwnd;
}

BOOL AutoflysWindowRegister(HINSTANCE hinstance)
{
	WNDCLASS wc;
	// 窗口句柄，hwnd变量是主窗口的句柄，这个程序中只用到了一个窗口。
	HWND hwnd;

	// Fill in the window class structure with parameters 
	// that describe the main window. 
	// 窗口类的样式，这里设置的样式表示窗口在大小变化是需要重绘
	wc.style = CS_HREDRAW | CS_VREDRAW;
	// 一个函数指针，这个函数用来处理窗口消息。 详见 MainWndProc函数的注释。
	wc.lpfnWndProc = AutoflyWindowProc;
	// no extra class memory 
	wc.cbClsExtra = 0;
	// no extra window memory
	wc.cbWndExtra = 0;
	// handle to instance 
	wc.hInstance = hinst;
	// hIcon成员用来指定窗口的图标
	// 这里直接使用LoadIcon函数加载了一个系统预定义的图标，开发人员可也可以自己创建图标。
	wc.hIcon = NULL;
	// Cursor是鼠标光标，这里是设定了鼠标光标的样式。
	// 直接使用LoadCursor API函数载入了一个系统预定义的光标样式，还有IDC_CROSS,IDC_HAND等样式 
	wc.hCursor = LoadCursor(NULL,
		IDC_CROSS);
	// GetStockObject的功能是加载一个系统预定义（在栈中）的GDI对象，
	// 这里加载的是一个白色的画刷，有关画刷和GDI对象，详见GDI说明。
	wc.hbrBackground = (HBRUSH)CreateSolidBrush(TRANS_BK_COLOR);
	// 窗口的菜单的资源名。
	wc.lpszMenuName = NULL;
	// 给窗口类起一个名字，在创建窗口时需要这个名字。
	wc.lpszClassName = CLASS_NAME_FLYS;
	// Register the window class. 

	if (!RegisterClass(&wc))
	{
		// 窗口注册失败，消息框提示，并退出。
		MessageBox(NULL, "创建窗口class失败", "错误！", MB_ICONERROR | MB_OK);
		return FALSE;
	}
	return TRUE;
}



/*******************************************************************************
* ##########   入口函数WinMain    ##########
*
* Windows应用程序的入口函数是WinMain函数，其地位和作用类似标准C语言的main函数
*
*******************************************************************************/

int WINAPI WinMain(
	HINSTANCE hinstance, // 程序实例句柄，在程序运行，进程创建后，由操作系统向应用程序传入
	HINSTANCE hPrevInstance, // 父进程的程序实例句柄
	LPSTR lpCmdLine,  // 命令行参数，地位和作用类似C语言main函数参数argc和argv,但是没有按空格进行切分
	int nCmdShow)   // 用于指明窗口是否需要显示的参数。
{
	BOOL fGotMessage;
	MSG msg;

	/*******************************************************************************
	* ##########   关于 API 函数   ##########
	*
	* API是 Application Programming Interface的缩写，即：应用程序编程接口。
	* API是Windows操作系统提供给应用程序调用的一系列功能的接口函数。用于应用程序调用操作系统的底层功能
	*
	* API函数的使用方法类似C语言的库函数，如printf，fopen，fread等。
	* 在VS环境中使用C或者C++进行编程是，只需#include <windows.h>即可调用大部分Windows API函数。
	*
	* 在下面一端代码中使用到的 LoadIcon LoadCursor GetStockObject RegisterClass CreateWindow等函数都是API
	*
	* Windows应用程序开发过程中的主要工作就是使用API。
	*
	*******************************************************************************/

	/*******************************************************************************
	* ##########   窗口类   ##########
	*
	* 在创建窗口之前，首先需要注册一个窗口类，窗口类可以理解为同一种类的窗口。
	* 一个窗口类可以创建多个窗口，属于同一窗口类的窗口具有相同的消息处理方法和相似的样式等
	*
	* 窗口类和C++中的类英文都是class，但是它们不是同一概念。
	* C++类使用class关键字定义，而窗口类是使用RegisterClass API函数向Windows系统注册。
	*
	* 下面的 WNDCLASS wc 是注册窗口类的 API函数RegisterClass的参数，是一个结构体类型，
	* 用来存储一个窗口类的各种属性
	*
	*******************************************************************************/

	if(BackGroundWindwowRegister(hinstance))
		hwndBackground = BackgroundWindowCreate(hinstance);

	if( FighterWindowRegister(hinstance))
		hwndFighter = FighterWindowCreate(hinstance);

	if (AutoflysWindowRegister(hinstance))
		hwndAutoflys = AutoflyWindowCreate(hinstance);
	



	/*******************************************************************************
	* ##########   MSG类型和消息    ##########
	*
	* Windows窗口应用程序是一种消息驱动的程序框架。
	* Windows窗口应用程序运行以后，其主线程就一直处于
	* "等待消息--获取消息--效应消息" 的循环之中，直到程序退出。
	*
	* 所谓消息是Windows系统特有的一种系统对象和机制，
	* 是操作系统对某些系统状态（如时钟）和用户操作（如鼠标点击）产生的系统中断进行封装以后，
	* 可以发送到应用程序，并由应用程序进行处理的用户态对象。
	*
	* "MSG"就是用来表示"消息"的数据类型。 这里定义了一个MSG类型的变量，变量名为msg
	*
	*******************************************************************************/


	// 以下进入消息循环。获取消息--翻译消息--分配消息（由窗口的消息处理函数来处理消息）
	while ((fGotMessage = GetMessage(&msg, (HWND)NULL, 0, 0)) != 0
		&& fGotMessage != -1)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}




LONG BackgroundCreate(HWND hwnd)
{
	//BITMAP bmp;
	hbmpBackground = LoadImage(NULL, BITMAP_FILE_BK,
		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	if (hbmpBackground == NULL)
	{
		MessageBox(hwnd, "bmp file not find", "ERROR!",
			MB_OK | MB_ICONERROR);
		ExitProcess(0);
	}

	return 0;
}

LONG AutoflysCreate(HWND hwnd)
{
	flys_init();
	SetTimer(hwnd, TIMER_ID, dwTimerElapse, NULL);

	return 0;
}

LONG BackgroundResizeAndMove(HWND hwnd, LPRECT lpRect)
{
	MoveWindow(hwndFighter,
		(lpRect->left + lpRect->right - FIGHTER_WIDTH) / 2,
		lpRect->bottom - FIGHTER_HEIGHT,
		FIGHTER_WIDTH,
		FIGHTER_HEIGHT,
		TRUE);
	return 0;
}

LONG BackgroundPaint(HWND hwnd)
{
	HDC hdc, hdcMem;
	//PAINTSTRUCT ps;
	RECT rect;

	unsigned int num, i;
	HBITMAP hbmMem;
	BITMAP bmp;

	hdc = GetDC(hwnd);
	GetClientRect(hwnd, &rect);
	// Create a memory device compatible with the above DC variable
	hdcMem = CreateCompatibleDC(hdc);
	
	SelectObject(hdcMem, hbmpBackground);
	
	GetObject(hbmpBackground, sizeof(BITMAP), &bmp);
	 
	StretchBlt(hdc,
		rect.left,	rect.top,
		rect.right - rect.left, rect.bottom - rect.top,
		hdcMem,
		0, 0, 
		bmp.bmWidth, bmp.bmHeight,
		SRCCOPY);

	DeleteObject(hdcMem);
	DeleteDC(hdcMem);
	ReleaseDC(hwnd, hdc);
	DeleteDC(hdc);
	return 0;
}

LONG FighterKeyDown(HWND hwnd, UINT vk)
{
	RECT rectFighter;
	switch (vk)
	{
	case VK_LEFT:
		GetWindowRect(hwndFighter, &rectFighter);
		MoveWindow(hwndFighter,
			rectFighter.left - FIGHTER_MOVE_STEP,
			rectFighter.top,
			FIGHTER_WIDTH,
			FIGHTER_HEIGHT,
			TRUE);
		break;
	case VK_RIGHT:
		GetWindowRect(hwndFighter, &rectFighter);
		MoveWindow(hwndFighter,
			rectFighter.left + FIGHTER_MOVE_STEP,
			rectFighter.top,
			FIGHTER_WIDTH,
			FIGHTER_HEIGHT,
			TRUE);
		break;
	case VK_UP:
		GetWindowRect(hwndFighter, &rectFighter);
		MoveWindow(hwndFighter,
			rectFighter.left,
			rectFighter.top - FIGHTER_MOVE_STEP,
			FIGHTER_WIDTH,
			FIGHTER_HEIGHT,
			TRUE);
		break;
	case VK_DOWN:
		GetWindowRect(hwndFighter, &rectFighter);
		MoveWindow(hwndFighter,
			rectFighter.left,
			rectFighter.top + FIGHTER_MOVE_STEP,
			FIGHTER_WIDTH,
			FIGHTER_HEIGHT,
			TRUE);
		break;
	case 'S':
	{
		POINT pt;
		GetWindowRect(hwndFighter, &rectFighter);

		pt.x = rectFighter.left;
		pt.y = rectFighter.top;

		//ScreenToClient(hwndMain, &pt);
		gen_bullet(pt.x + FIGHTER_WIDTH/2, pt.y);
		//PlaySound("C:\\Windows\\Media\\ir_end.wav", NULL, SND_FILENAME);
	}
	break;
	default:
		break;
	}
	return 0;
}

LONG AutoFlysTimer(HWND hwnd)
{
	
	unsigned int num, i;
	LPAUTO_FLY auto_fly;
	
	flys_move_step();
	
	num = get_flys_num();

	for (i = 0; i < num; i++)
	{
		auto_fly = get_fly_at(i);
		if (auto_fly->state == FLY_HIT)
		{
			// todo 爆炸；
		}
	}

	destory_fly_by_state();
	return 0;
}
