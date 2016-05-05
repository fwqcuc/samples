// InjectRemoteProc.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#pragma comment(lib, "advapi32.lib")

TCHAR * DLL_NAME = L"InjectDll.dll";

BOOL InjectRemoteThread(DWORD ProcessID);

int main() {
	TCHAR dllpathBuffer[MAX_PATH];
	GetFullPathName(DLL_NAME, MAX_PATH, dllpathBuffer, NULL);
	DLL_NAME = dllpathBuffer;

	printf("Please enter ProcessName/PID to inject.\n>");
	char ProcessName[100];
	gets_s(ProcessName, 100);
	char * pEnd = nullptr;
	// Convert PID string to DWORD
	DWORD dwPID = strtoul(ProcessName, &pEnd, 10);

	if ((pEnd - ProcessName) == strlen(ProcessName)) {
		printf("Read PID. %u", dwPID);
		InjectRemoteThread(dwPID);
	}
	else {
		//Get first process in list
		HANDLE hProcessSnap = NULL;
		PROCESSENTRY32 peProcess = { 0 };
		hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
		if (hProcessSnap == INVALID_HANDLE_VALUE) {
			printf("Unable to get process list (%d).\n", GetLastError());
			return 0;
		}
		peProcess.dwSize = sizeof(PROCESSENTRY32);

		WCHAR wProcessName[100];
		StringCbPrintf(wProcessName, 100, L"%S", ProcessName);
		wprintf(L"Try to find proccess name '%s' \n", wProcessName);


		bool bFound = false;
		if (Process32First(hProcessSnap, &peProcess)) {
			do {
				if (!wcscmp(peProcess.szExeFile, wProcessName)) {
					wprintf(L"\n Found %s ProcessID: %d \n", wProcessName, peProcess.th32ProcessID);
					bFound = true;
					InjectRemoteThread(peProcess.th32ProcessID);
				}
			} while (Process32Next(hProcessSnap, &peProcess));
		}
		if (!bFound) {
			wprintf(L"\n Process '%s' not found!\n", wProcessName);
		}
	}




	return 0;
}

BOOL InjectRemoteThread(DWORD ProcessID) {

	if (!ProcessID) {
		MessageBox(NULL, (LPCWSTR)GetLastError(), L"An error occured, ProcessID Error.", NULL);
		return 0;
	}

	HANDLE RemoteProc = OpenProcess(PROCESS_VM_OPERATION | PROCESS_VM_WRITE | PROCESS_CREATE_THREAD | PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, ProcessID);
	
	if (!RemoteProc){
		MessageBox(NULL, (LPCWSTR)GetLastError(), L"An error occured, Fail to OpenProc", NULL);
		return 0;
	}

	LPVOID LoadLibAddress = (LPVOID)GetProcAddress(
		GetModuleHandleA("kernel32.dll"),
		"LoadLibraryW");

	//CreateThread(
	//	NULL,
	//	NULL,
	//	(LPTHREAD_START_ROUTINE)LoadLibAddress,
	//	(LPVOID)DLL_NAME,
	//	NULL,
	//	NULL);




	LPVOID MemAlloc = (LPVOID)VirtualAllocEx(
		RemoteProc,
		NULL,
		(wcslen(DLL_NAME) + 1) * 2,
//		strlen(DLL_NAME) + 1,
		MEM_RESERVE | MEM_COMMIT,
		PAGE_READWRITE);

	printf("\n Memory Address to Write:0x%08x \n", MemAlloc);

	WriteProcessMemory(
		RemoteProc,
		(LPVOID)MemAlloc,
		DLL_NAME,
		(wcslen(DLL_NAME) + 1) * 2,
//		strlen(DLL_NAME) + 1,
		NULL);

	CreateRemoteThread(
		RemoteProc,
		NULL,
		NULL,
		(LPTHREAD_START_ROUTINE)LoadLibAddress,
		(LPVOID)MemAlloc,
		NULL,
		NULL);



	CloseHandle(RemoteProc);
	VirtualFreeEx(
		RemoteProc,
		(LPVOID)MemAlloc,
		0,
		MEM_RELEASE | MEM_DECOMMIT);

	return 1;
}

