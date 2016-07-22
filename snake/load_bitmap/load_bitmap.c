
#include <windows.h>

HINSTANCE hInst;
LRESULT CALLBACK WindProcedure(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX  WndCls;
	static char szAppName[] = "BitmapIntro";
	MSG         Msg;

	hInst = hInstance;
	WndCls.cbSize = sizeof(WndCls);
	WndCls.style = CS_OWNDC | CS_VREDRAW | CS_HREDRAW;
	WndCls.lpfnWndProc = WindProcedure;
	WndCls.cbClsExtra = 0;
	WndCls.cbWndExtra = 0;
	WndCls.hInstance = hInst;
	WndCls.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndCls.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndCls.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndCls.lpszMenuName = NULL;
	WndCls.lpszClassName = szAppName;
	WndCls.hIconSm = LoadIcon(hInstance, IDI_APPLICATION);
	RegisterClassEx(&WndCls);

	CreateWindowEx(WS_EX_OVERLAPPEDWINDOW,
		szAppName,
		"Bitmaps Fundamentals",
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL);

	while (GetMessage(&Msg, NULL, 0, 0))
	{
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}

	return Msg.wParam;
}

HBITMAP bmpExercising;

LRESULT CALLBACK WindProcedure(HWND hWnd, UINT Msg,
	WPARAM wParam, LPARAM lParam)
{
	HDC hDC, MemDCExercising;
	PAINTSTRUCT Ps;


	switch (Msg)
	{
	case WM_CREATE:
		bmpExercising = LoadImage(NULL, "bitmap1.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		// Load the bitmap from the resource
		if (bmpExercising == NULL)
		{
			MessageBox(NULL, "CANOT FIND bitmap1.bmp FILE", "ERROR", MB_OK|MB_ICONERROR);
			ExitProcess(0);
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(WM_QUIT);
		break;
	case WM_PAINT:
		hDC = BeginPaint(hWnd, &Ps);


		// Create a memory device compatible with the above DC variable
		MemDCExercising = CreateCompatibleDC(hDC);
		// Select the new bitmap
		SelectObject(MemDCExercising, bmpExercising);

		// Copy the bits from the memory DC into the current dc
		BitBlt(hDC, 10, 10, 450, 400, MemDCExercising, 0, 0, SRCCOPY);

		// Restore the old bitmap
		DeleteDC(MemDCExercising);
		DeleteObject(bmpExercising);
		EndPaint(hWnd, &Ps);
		break;
	default:
		return DefWindowProc(hWnd, Msg, wParam, lParam);
	}
	return DefWindowProc(hWnd, Msg, wParam, lParam);
}