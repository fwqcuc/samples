#include <Windows.h>
#include "auto_fly.h"



LONG CALLBACK BackGroundWindowProc(
	HWND hwnd, //
	UINT msg, // 消息
	WPARAM wParam, // 消息参数，不同的消息有不同的意义，详见MSDN中每个消息的文档
	LPARAM lParam); // 消息参数，不同的消息有不同的意义，详见MSDN中每个消息的文档


BOOL BackGroundWindwowRegister(HINSTANCE hinstance);

HWND BackgroundWindowCreate(HINSTANCE hinstance);

LONG CALLBACK FightWindowProc(
	HWND hwnd, //
	UINT msg, // 消息
	WPARAM wParam, // 消息参数，不同的消息有不同的意义，详见MSDN中每个消息的文档
	LPARAM lParam); // 消息参数，不同的消息有不同的意义，详见MSDN中每个消息的文档

LONG FighterCreate(HWND hwnd);
HWND FightWindowCreate(HINSTANCE hinstance);

BOOL FightWindowRegister(HINSTANCE hinstance);

LONG AutoflysPaint(HWND hwnd);
LONG CALLBACK AutoflyWindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
HWND AutoflyWindowCreate(HINSTANCE hinstance);
BOOL AutoflysWindowRegister(HINSTANCE hinstance);


LONG BackgroundCreate(HWND hwnd);

LONG AutoflysCreate(HWND hwnd);
LONG BackgroundResizeAndMove(HWND hwnd, LPRECT lpRect);
LONG BackgroundPaint(HWND hwnd);
LONG OnKeydown(HWND hwnd, UINT vk);

LONG AutoFlysTimer(HWND hwnd);