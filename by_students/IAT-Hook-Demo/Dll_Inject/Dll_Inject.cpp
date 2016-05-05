// Dll_Inject.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "Dll_Inject.h"


// 这是导出变量的一个示例
DLL_INJECT_API int nDll_Inject = 0;

// 这是导出函数的一个示例。
DLL_INJECT_API int fnDll_Inject(void) {
	return 42;
}

// 这是已导出类的构造函数。
// 有关类定义的信息，请参阅 Dll_Inject.h
CDll_Inject::CDll_Inject() {
	return;
}
