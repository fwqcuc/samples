#pragma once
#include "stdafx.h"

BOOL ModifyImportTable(
	IMAGE_IMPORT_DESCRIPTOR* iid,
	void* target,
	void* replacement
);

BOOL InstallHook(
	LPCSTR module,
	LPCSTR function,
	void* hook,
	void** original
);
