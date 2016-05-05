#include "stdafx.h"
#include "hookFunc.h"

#pragma comment(lib, "Dbghelp.lib")

BOOL ModifyImportTable(IMAGE_IMPORT_DESCRIPTOR* iid, void* target, void* replacement) {
	IMAGE_THUNK_DATA* itd = (IMAGE_THUNK_DATA*)(
		((char*)GetModuleHandle(NULL)) + iid->FirstThunk);

	while (itd->u1.Function) {
		if (((void*)itd->u1.Function) == target) {
			// Temporary change access to memory area to READWRITE
			MEMORY_BASIC_INFORMATION mbi;
			VirtualQuery(itd, &mbi, sizeof(MEMORY_BASIC_INFORMATION));
			VirtualProtect(mbi.BaseAddress, mbi.RegionSize, PAGE_READWRITE, &mbi.Protect);
					
			char buffer[100];

			sprintf_s(buffer, 100, "Memory Address to Write:0x%08x", (int)((void**)itd));
			MessageBoxA(NULL, buffer, "Info", MB_ICONINFORMATION);

			sprintf_s(buffer, 100, "We Want Change it to:0x%08x", (int)replacement);
			MessageBoxA(NULL, buffer, "Info", MB_ICONINFORMATION);

			// Replace entry!!
			*((void**)itd) = replacement;
			// Restore memory permissions
			
			VirtualProtect(mbi.BaseAddress, mbi.RegionSize, mbi.Protect, &mbi.Protect);

			sprintf_s(buffer, 100, "FindNextFileW Now Point:0x%08x", (int)*((void**)itd));
			MessageBoxA(NULL, buffer, "Info", MB_ICONINFORMATION);

			VirtualQuery(itd, &mbi, sizeof(MEMORY_BASIC_INFORMATION));
			sprintf_s(buffer, 100, "VirtualProtect Now :0x%08x", mbi.Protect);
			MessageBoxA(NULL, buffer, "Info", MB_ICONINFORMATION);


			return TRUE;
		}

		itd += 1;
	}
	return FALSE;
}

BOOL InstallHook(LPCSTR module, LPCSTR function, void* hook, void** original) {
	HMODULE process = GetModuleHandle(NULL);

	// Save original address to function
	*original = (void*)GetProcAddress(
		GetModuleHandleA(module), function);

	ULONG entrySize;

	IMAGE_IMPORT_DESCRIPTOR* iid =
		(IMAGE_IMPORT_DESCRIPTOR*)ImageDirectoryEntryToData(
			process,
			1,
			IMAGE_DIRECTORY_ENTRY_IMPORT,
			&entrySize);

	// Search for module
	while (iid->Name) {
		const char* name = ((char*)process) + iid->Name;

		if (_stricmp(name, module) == 0) {
			return ModifyImportTable(iid, *original, hook);
		}
		iid += 1;
	}

	return FALSE;
}
