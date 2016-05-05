

#include "stdafx.h"


BOOL ModifyImportTable(IMAGE_IMPORT_DESCRIPTOR* iid, void* target, void* replacement);
BOOL InstallHook(LPCSTR module, LPCSTR function, void* hook, void** original);
int __stdcall HookedMessageBoxA(HWND hWnd, LPCSTR lpText, LPCSTR lpCaption, UINT uType);
int(__stdcall *RealMessageBoxA)(HWND, LPCSTR, LPCSTR, UINT);

