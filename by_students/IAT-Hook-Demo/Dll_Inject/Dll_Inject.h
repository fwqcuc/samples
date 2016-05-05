// 下列 ifdef 块是创建使从 DLL 导出更简单的
// 宏的标准方法。此 DLL 中的所有文件都是用命令行上定义的 DLL_INJECT_EXPORTS
// 符号编译的。在使用此 DLL 的
// 任何其他项目上不应定义此符号。这样，源文件中包含此文件的任何其他项目都会将
// DLL_INJECT_API 函数视为是从 DLL 导入的，而此 DLL 则将用此宏定义的
// 符号视为是被导出的。
#ifdef DLL_INJECT_EXPORTS
#define DLL_INJECT_API __declspec(dllexport)
#else
#define DLL_INJECT_API __declspec(dllimport)
#endif

// 此类是从 Dll_Inject.dll 导出的
class DLL_INJECT_API CDll_Inject {
public:
	CDll_Inject(void);

	// TODO:  在此添加您的方法。
};

extern DLL_INJECT_API int nDll_Inject;

DLL_INJECT_API int fnDll_Inject(void);

//DLL_INJECT_API BOOL HookFindNextFileW(
//	HANDLE hFindFile,
//	LPWIN32_FIND_DATAW lpFindFileData
//	);
