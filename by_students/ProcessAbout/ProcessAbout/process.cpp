#include <windows.h>
#include <tlhelp32.h> //tlhelp32.h主要是用于枚举系统中某个时刻的进程，线程，模块，堆。
#include <tchar.h>	  //tchar.h兼容字符集ASCII和UNICODE.当没有定义_UNICODE宏时，TCHAR = char，_tcslen = strlen；
					  //当定义了_UNICODE宏时，TCHAR = wchar_t ， _tcslen = wcslen 。

//  Forward declarations:函数声明
BOOL GetProcessList();
BOOL ListProcessModules(DWORD dwPID);
BOOL ListProcessThreads(DWORD dwOwnerPID);
void printError(TCHAR* msg);

int main(void)
{
	GetProcessList();
	system("pause");

	return 0;
}
/*
快照:snapshot, 类似于screen-shot(屏幕快照,按prtscr键时抓的当前windows全屏)
进程快照就是当前系统中正在运行的所有进程列表,一般用CreateToolhelp32Snapshot得到.

在第一次调用某个函数枚举进程的时候,可以得到当前系统进程信息,而在第二次试图得到
这个信息的时候,这个信息可能已经发生了变化.所以这个信息是一个"照片",是过去某个时刻的情况.

进程的创建是一个"漫长"的过程,在枚举进程函数被调用过程中,进程可能发生了变化,所以得到的仍然是某个时刻的"照片".
*/


BOOL GetProcessList()//获取进程列表
{
	HANDLE hProcessSnap;//进程快照句柄
	HANDLE hProcess;//进程句柄
	PROCESSENTRY32 pe32;//快照进程信息
	/*PROCESSENTRY32:用来存放快照进程信息的一个结构体。（存放进程信息和调用成员输出进程信息）
	用 Process32First指向第一个进程信息，并将进程信息抽取到PROCESSENTRY32中。
	用Process32Next指向下一条进程信息。*/
	DWORD dwPriorityClass;//优先级
	
	// Take a snapshot of all processes in the system.
	hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	/*
HANDLE WINAPI CreateToolhelp32Snapshot( 获取进程、堆、模块和线程的快照，以句柄返回
DWORD dwFlags, 参数 TH32CS_SNAPPROCESS 表示在快照中包含系统中所有的进程
DWORD th32ProcessID， 参数 0 表示在表示快照当前进程
);
	*/
	if (hProcessSnap == INVALID_HANDLE_VALUE)
	{ // //如果调用CreateToolhelp32Snapshot失败则报错
		printError(TEXT("CreateToolhelp32Snapshot (of processes)"));
		return(FALSE);
	}

	// Set the size of the structure before using it.使用结构之前，先设置它的大小
	pe32.dwSize = sizeof(PROCESSENTRY32);

	// Retrieve information about the first process,
	// and exit if unsuccessful
	if (!Process32First(hProcessSnap, &pe32))
		/*BOOL WINAPI Process32First(获得第一个进程
		HANDLE hSnapshot,//_in快照句柄
		LPPROCESSENTRY32 lppe//_out存放信息位置
		);
		*/
	{
		printError(TEXT("Process32First")); // show cause of failure
		CloseHandle(hProcessSnap);          // clean the snapshot object
		return(FALSE);
	}

	// Now walk the snapshot of processes, and
	// display information about each process in turn
	do
	{
		_tprintf(TEXT("\n\n====================================================="));
		_tprintf(TEXT("\n Process Name:  %s"),pe32.szExeFile);
		
		_tprintf(TEXT("\n-------------------------------------------------------"));

		// Retrieve the priority class.获取优先级
		dwPriorityClass = 0;
		//hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pe32.th32ProcessID);
		hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pe32.th32ProcessID);
		/*
HANDLE OpenProcess( 用来打开一个已存在的进程对象，并返回进程的句柄
DWORD dwDesiredAccess, //渴望得到的访问权限（标志）
BOOL bInheritHandle, // 是否继承句柄
DWORD dwProcessId// 进程标示符
);
		*/
		if (hProcess == NULL)
			printError(TEXT("OpenProcess"));
		else
		{
			dwPriorityClass = GetPriorityClass(hProcess);
			/*
			GetPriorityClass:获取特定进程的优先级别
			返回指向进程的优先级。返回的优先级以及它的每一个线程的优先级来决定每一个线程的基础优先水平。
			*/
			if (!dwPriorityClass)
				printError(TEXT("GetPriorityClass"));
			CloseHandle(hProcess);
		}

		_tprintf(TEXT("\n  Process ID		 = 0x%08X"), pe32.th32ProcessID);
		_tprintf(TEXT("\n  Thread count		 = %d"), pe32.cntThreads);
		_tprintf(TEXT("\n  Parent process ID = 0x%08X"), pe32.th32ParentProcessID);
		_tprintf(TEXT("\n  Priority base	 = %d"), pe32.pcPriClassBase);
		if (dwPriorityClass)
			_tprintf(TEXT("\n Priority class = %d"), dwPriorityClass);

		// List the modules and threads associated with this process列举与当前进程相关的线程和模块
		ListProcessModules(pe32.th32ProcessID);//函数调用
		ListProcessThreads(pe32.th32ProcessID);//

	} while (Process32Next(hProcessSnap, &pe32));
	/*BOOL WINAPI Process32Next(获得下一进程的句柄
HANDLE hSnapshot,
LPPROCESSENTRY32 lppe
);
	*/
	//循环直到Process32Next返回值为FALSE
	CloseHandle(hProcessSnap);
	return(TRUE);
}


BOOL ListProcessModules(DWORD dwPID)
{
	HANDLE hModuleSnap = INVALID_HANDLE_VALUE;//置为无效值，不存在模块时返回上级函数
	MODULEENTRY32 me32;
	/*MODULEENTRY32:模块入口结构体
	用来存放模块信息的一个结构体。
	*/
	// Take a snapshot of all modules in the specified process.
	hModuleSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, dwPID);
	/*获取模块快照，使用相同的函数，改变参数，TH32CS_SNAPMODULE标识快照当前进程的所有模块，
	dwPID标识对特定进程
	*/
	if (hModuleSnap == INVALID_HANDLE_VALUE)
	{
		printError(TEXT("CreateToolhelp32Snapshot (of modules)"));
		return(FALSE);
	}

	// Set the size of the structure before using it.使用前设置结构体大小
	me32.dwSize = sizeof(MODULEENTRY32);

	// Retrieve information about the first module,
	// and exit if unsuccessful
	if (!Module32First(hModuleSnap, &me32))
	{//获取第一个模块，其信息存放于结构体me32中
		printError(TEXT("Module32First"));  // show cause of failure
		CloseHandle(hModuleSnap);           // clean the snapshot object
		return(FALSE);
	}

	// Now walk the module list of the process,
	// and display information about each module
	do
	{
		_tprintf(TEXT("\n\n    MODULE NAME   : %s"), me32.szModule);
		_tprintf(TEXT("\n     Executable     = %s"), me32.szExePath);
		_tprintf(TEXT("\n     Process ID     = 0x%08X"), me32.th32ProcessID);
		_tprintf(TEXT("\n     Ref count (g)  = 0x%04X"), me32.GlblcntUsage);
		_tprintf(TEXT("\n     Ref count (p)  = 0x%04X"), me32.ProccntUsage);
		_tprintf(TEXT("\n     Base address   = 0x%08X"), (DWORD)me32.modBaseAddr);
		_tprintf(TEXT("\n     Base size      = %d"), me32.modBaseSize);

	} while (Module32Next(hModuleSnap, &me32));
	//获取下一模块。
	//循环直到Module32Next返回值为FALSE
	CloseHandle(hModuleSnap);
	return(TRUE);
}

BOOL ListProcessThreads(DWORD dwOwnerPID)
{
	HANDLE hThreadSnap = INVALID_HANDLE_VALUE;
	THREADENTRY32 te32;
	/*THREADENTRY32:线程入口结构体
	列举线程的相关信息
	*/
	// Take a snapshot of all running threads  
	hThreadSnap = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
	/*获取线程快照，使用相同的函数，改变参数，TH32CS_SNAPTHREAD标识快照当前所有线程
	*/
	if (hThreadSnap == INVALID_HANDLE_VALUE)
		return(FALSE);

	// Fill in the size of the structure before using it. 
	te32.dwSize = sizeof(THREADENTRY32);

	// Retrieve information about the first thread,
	// and exit if unsuccessful
	if (!Thread32First(hThreadSnap, &te32))
	{//获取第一个线程，其信息存放于结构体te32中
		printError(TEXT("Thread32First")); // show cause of failure
		CloseHandle(hThreadSnap);          // clean the snapshot object
		return(FALSE);
	}

	// Now walk the thread list of the system,
	// and display information about each thread
	// associated with the specified process
	do
	{
		if (te32.th32OwnerProcessID == dwOwnerPID)
		{
			_tprintf(TEXT("\n\n   Thread ID      = 0x%08X"), te32.th32ThreadID);
			_tprintf(TEXT("\n     Base priority  = %d"), te32.tpBasePri);
			_tprintf(TEXT("\n     Delta priority = %d"), te32.tpDeltaPri);
			_tprintf(TEXT("\n"));
		}
	} while (Thread32Next(hThreadSnap, &te32));

	CloseHandle(hThreadSnap);
	return(TRUE);
}

void printError(TCHAR* msg)
{
	DWORD eNum;
	TCHAR sysMsg[256];
	TCHAR* p;

	eNum = GetLastError();
	FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL, eNum,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
		sysMsg, 256, NULL);

	// Trim the end of the line and terminate it with a null
	p = sysMsg;
	while ((*p > 31) || (*p == 9))
		++p;
	do { *p-- = 0; } while ((p >= sysMsg) &&
		((*p == '.') || (*p < 33)));

	// Display the message
	_tprintf(TEXT("\n  WARNING: %s failed with error %d (%s)"), msg, eNum, sysMsg);
}
