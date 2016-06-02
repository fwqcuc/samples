#include "imagehlp_pe.h"

void PrintPeFileFormat(WORD Characteristics){
	printf("File Type:\n");
	if(Characteristics&IMAGE_FILE_RELOCS_STRIPPED)
		printf("RELOCS STRIPPED\n");
	if(Characteristics&IMAGE_FILE_EXECUTABLE_IMAGE)
		printf("EXECUTABLE IMAGE\n");
	if(Characteristics&IMAGE_FILE_LINE_NUMS_STRIPPED)
		printf("LINE_NUMS STRIPPED\n");
	if(Characteristics&IMAGE_FILE_LOCAL_SYMS_STRIPPED)
		printf("LOCAL SYMS STRIPPED\n");
	if(Characteristics&IMAGE_FILE_AGGRESIVE_WS_TRIM)
		printf("AGGRESIVE WS TRIM\n");
	if(Characteristics&IMAGE_FILE_LARGE_ADDRESS_AWARE)
		printf("LARGE ADDRESS AWARE\n");
	if(Characteristics&IMAGE_FILE_BYTES_REVERSED_LO)
		printf("BYTES REVERSED LO\n");
	if(Characteristics&IMAGE_FILE_32BIT_MACHINE)
		printf("32BIT MACHINE\n");
	if(Characteristics&IMAGE_FILE_DEBUG_STRIPPED)
		printf("DEBUG STRIPPED\n");
	if(Characteristics&IMAGE_FILE_REMOVABLE_RUN_FROM_SWAP)
		printf("REMOVABLE RUN FROM SWAP\n");
	if(Characteristics&IMAGE_FILE_NET_RUN_FROM_SWAP)
		printf("NET_RUN FROM SWAP\n");
	if(Characteristics&IMAGE_FILE_SYSTEM)
		printf("SYSTEM\n");
	if(Characteristics&IMAGE_FILE_DLL)
		printf("DLL\n");
	if(Characteristics&IMAGE_FILE_UP_SYSTEM_ONLY)
		printf("UP SYSTEM ONLY\n");
	if(Characteristics&IMAGE_FILE_BYTES_REVERSED_HI)
		printf("BYTES REVERSED HI\n");
}

int GetPeHeaders(char*path)
{
	/**********START**********/
	HANDLE hFile,hFileMap;
	OFSTRUCT OpenBuff;
	DWORD dwSectionCount;
	DWORD dwSection=0;
	LPVOID lpFile;
	PIMAGE_DOS_HEADER pDosHeader;
	PIMAGE_NT_HEADERS pNtHeaders;
	PIMAGE_SECTION_HEADER pSectionHeader;

	/**********打开PE文件**********/
	printf("Dump of file %s:\n",path);

	hFile = (HANDLE)OpenFile(
		path,
		&OpenBuff,
		OF_READ
		);

	if(hFile==INVALID_HANDLE_VALUE)
		return -1;

	hFileMap = CreateFileMapping(
		hFile,
		0,
		PAGE_READONLY,
		0,
		0,
		0
		);

	lpFile = MapViewOfFile(hFileMap,FILE_MAP_READ,0,0,0);

	/**********IMAGE_DOS_HEADER**********/
	pDosHeader = (PIMAGE_DOS_HEADER)lpFile;
	printf("IMAGE_DOS_HEADER结构:\n");
	printf("e_magic　	: %04x\n",pDosHeader->e_magic);
	printf("e_cblp　　	: %04x\n",pDosHeader->e_cblp); 
	printf("e_cp　　　	: %04x\n",pDosHeader->e_cp); 
	printf("e_crlc　　	: %04x\n",pDosHeader->e_crlc); 
	printf("e_cparhdr	: %04x\n",pDosHeader->e_cparhdr); 
	printf("e_minalloc	: %04x\n",pDosHeader->e_minalloc); 
	printf("e_maxalloc	: %04x\n",pDosHeader->e_maxalloc); 
	printf("e_ss　　　	: %04x\n",pDosHeader->e_ss); 
	printf("e_sp　　　	: %04x\n",pDosHeader->e_sp); 
	printf("e_csum　　	: %04x\n",pDosHeader->e_csum); 
	printf("e_ip　　　	: %04x\n",pDosHeader->e_ip); 
	printf("e_cs　　　	: %04x\n",pDosHeader->e_cs); 
	printf("e_lfarlc　	: %04x\n",pDosHeader->e_lfarlc); 
	printf("e_ovno　　	: %04x\n",pDosHeader->e_ovno); 
	printf("e_res[0]　	: %04x\n",pDosHeader->e_res[0]); 
	printf("e_oemid　	: %04x\n",pDosHeader->e_oemid); 
	printf("e_oeminfo	: %04x\n",pDosHeader->e_oeminfo); 
	printf("res2[0] 　	: %04x\n",pDosHeader->e_res2[0]); 
	printf("lfanew　　	: %08x\n",pDosHeader->e_lfanew); 

	/**********IMAGE_NT_HEADER**********/
	printf("\nIMAGE_NT_HEADER结构:\n"); 
	pNtHeaders = (PIMAGE_NT_HEADERS)((DWORD)lpFile+pDosHeader->e_lfanew);

	/**********PE文件标志**********/
    printf("Signature : %04X\n",pNtHeaders->Signature); 
	if((pDosHeader->e_magic ==IMAGE_DOS_SIGNATURE)&&(pNtHeaders->Signature== IMAGE_NT_SIGNATURE)) 
		printf("有效的PE文件\n");
	else
		printf("无效的PE文件\n"); 

	/**********IMAGE_FILE_HEADER**********/
	printf("\nIMAGE_FILE_HEADER结构:\n"); 
	printf("Machine　　　　　　　: %04X\n",pNtHeaders->FileHeader.Machine);
	printf("NumberOfSections　　 : %04X\n",pNtHeaders->FileHeader.NumberOfSections); 
	printf("TimeDateStamp　　　　: %08X\n",pNtHeaders->FileHeader.TimeDateStamp); 
	printf("PointerToSymbolTable : %08X\n",pNtHeaders->FileHeader.PointerToSymbolTable); 
	printf("NumberOfSymbols　　　: %08X\n",pNtHeaders->FileHeader.NumberOfSymbols); 
	printf("SizeOfOptionalHeader : %04X\n",pNtHeaders->FileHeader.SizeOfOptionalHeader); 
	printf("Characteristics　　　: %04X\n",pNtHeaders->FileHeader.Characteristics);
	PrintPeFileFormat(pNtHeaders->FileHeader.Characteristics);

	/**********IMAGE_OPTION_HEADER**********/
    printf("\nIMAGE_OPTION_HEADER结构:\n");
    printf("Magic                                 : %04X\n",pNtHeaders->OptionalHeader.Magic);
    printf("MajorLinkerVersion　	       　     : %02X\n",pNtHeaders->OptionalHeader.MajorLinkerVersion);
    printf("MinorLinkerVersion　                  : %02X\n",pNtHeaders->OptionalHeader.MinorLinkerVersion);
    printf("SizeOfCode　　　　　 　               : %08X\n",pNtHeaders->OptionalHeader.SizeOfCode);
    printf("SizeOfInitializedData                 : %08X\n",pNtHeaders->OptionalHeader.SizeOfInitializedData);
    printf("SizeOfUninitializedData               : %08X\n",pNtHeaders->OptionalHeader.SizeOfUninitializedData);
    printf("AddressOfEntryPoint　　               : %08X\n",pNtHeaders->OptionalHeader.AddressOfEntryPoint);
    printf("BaseOfCode　　　　　　            　　: %08X\n",pNtHeaders->OptionalHeader.BaseOfCode);
    printf("BaseOfData　　　　                  　: %08X\n",pNtHeaders->OptionalHeader.BaseOfData);
    printf("ImageBase　　　　  　　               : %08X\n",pNtHeaders->OptionalHeader.ImageBase);
    printf("SectionAlignment　　         　       : %08X\n",pNtHeaders->OptionalHeader.SectionAlignment);
    printf("FileAlignment　　　　	              : %08X\n",pNtHeaders->OptionalHeader.FileAlignment);
    printf("MajorOperatingSystemVersion           : %04X\n",pNtHeaders->OptionalHeader.MajorOperatingSystemVersion);
    printf("MinorOperatingSystemVersion           : %04X\n",pNtHeaders->OptionalHeader.MinorOperatingSystemVersion);
    printf("MajorImageVersion　　　　　           : %04X\n",pNtHeaders->OptionalHeader.MajorImageVersion);
    printf("MinorImageVersion　　　　           　: %04X\n",pNtHeaders->OptionalHeader.MinorImageVersion);
    printf("MajorSubsystemVersion　　　           : %04X\n",pNtHeaders->OptionalHeader.MajorSubsystemVersion);
    printf("MinorSubsystemVersion　　           　: %04X\n",pNtHeaders->OptionalHeader.MinorSubsystemVersion);
    printf("Win32VersionValue　　　　             : %08X\n",pNtHeaders->OptionalHeader.Win32VersionValue);
    printf("SizeOfImage                           : %08X\n",pNtHeaders->OptionalHeader.SizeOfImage);
    printf("SizeOfHeaders　　　　	              : %08X\n",pNtHeaders->OptionalHeader.SizeOfHeaders);
    printf("CheckSum     　　　　                 : %08X\n",pNtHeaders->OptionalHeader.CheckSum);
    printf("Subsystem　　　                       : %04X\n",pNtHeaders->OptionalHeader.Subsystem);
    printf("DllCharacteristics　　　              : %04X\n",pNtHeaders->OptionalHeader.DllCharacteristics);
    printf("SizeOfStackReserve　　　　            : %08X\n",pNtHeaders->OptionalHeader.SizeOfStackReserve);
    printf("SizeOfStackCommit                     : %08X\n",pNtHeaders->OptionalHeader.SizeOfStackCommit);
    printf("SizeOfHeapReserve                     : %08X\n",pNtHeaders->OptionalHeader.SizeOfHeapReserve);
    printf("SizeOfHeapCommit　　                  : %08X\n",pNtHeaders->OptionalHeader.SizeOfHeapCommit);
    printf("LoaderFlags　　　　　　             　: %08X\n",pNtHeaders->OptionalHeader.LoaderFlags);
    printf("NumberOfRvaAndSizes                   : %08X\n",pNtHeaders->OptionalHeader.NumberOfRvaAndSizes);
    printf("EXPORT DIRECTORY VA                   : %08X\n",pNtHeaders->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress);
	printf("EXPORT DIRECTORY Size                 : %08X\n",pNtHeaders->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].Size);
    printf("IMPORT DIRECTORY VA                   : %08X\n",pNtHeaders->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress);
	printf("IMPORT DIRECTORY Size                 : %08X\n",pNtHeaders->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].Size);
    printf("Resource Directory VA                 : %08X\n",pNtHeaders->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_RESOURCE].VirtualAddress);
	printf("Resource Directory Size               : %08X\n",pNtHeaders->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_RESOURCE].Size);
    printf("Exception Directory VA                : %08X\n",pNtHeaders->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXCEPTION].VirtualAddress);
	printf("Exception Directory Size              : %08X\n",pNtHeaders->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXCEPTION].Size);
    printf("Security Directory VA                 : %08X\n",pNtHeaders->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_SECURITY].VirtualAddress);
	printf("Security Directory Size               : %08X\n",pNtHeaders->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_SECURITY].Size);
    printf("Base Relocation Table VA              : %08X\n",pNtHeaders->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC].VirtualAddress);
	printf("Base Relocation Table Size            : %08X\n",pNtHeaders->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC].Size);
    printf("Debug Directory VA                    : %08X\n",pNtHeaders->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_DEBUG].VirtualAddress);
	printf("Debug Directory Size                  : %08X\n",pNtHeaders->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_DEBUG].Size);
    printf("Architecture Specific Data VA         : %08X\n",pNtHeaders->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_ARCHITECTURE].VirtualAddress);
	printf("Architecture Specific Data Size       : %08X\n",pNtHeaders->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_ARCHITECTURE].Size);
    printf("RVA of GP VA                          : %08X\n",pNtHeaders->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_GLOBALPTR].VirtualAddress);
	printf("RVA of GP Size                        : %08X\n",pNtHeaders->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_GLOBALPTR].Size);
    printf("TLS Directory VA                      : %08X\n",pNtHeaders->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_TLS].VirtualAddress);
	printf("TLS Directory Size                    : %08X\n",pNtHeaders->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_TLS].Size);
    printf("Load Configuration Directory VA       : %08X\n",pNtHeaders->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_LOAD_CONFIG].VirtualAddress);
	printf("Load Configuration Directory Size     : %08X\n",pNtHeaders->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_LOAD_CONFIG].Size);
    printf("Bound Import Directory in headers VA  : %08X\n",pNtHeaders->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BOUND_IMPORT].VirtualAddress);
	printf("Bound Import Directory in headers Size: %08X\n",pNtHeaders->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BOUND_IMPORT].Size);
    printf("Import Address Table VA               : %08X\n",pNtHeaders->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IAT].VirtualAddress);
	printf("Import Address Table Size             : %08X\n",pNtHeaders->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IAT].Size);
    printf("Delay Load Import Descriptors VA      : %08X\n",pNtHeaders->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_DELAY_IMPORT].VirtualAddress);
	printf("Delay Load Import Descriptors Size    : %08X\n",pNtHeaders->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_DELAY_IMPORT].Size);
    printf("COM Runtime descriptor VA             : %08X\n",pNtHeaders->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_COM_DESCRIPTOR].VirtualAddress);
	printf("COM Runtime descriptor Size           : %08X\n",pNtHeaders->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_COM_DESCRIPTOR].Size);

	/**********IMAGE_SECTION_HEADER**********/
	dwSectionCount = pNtHeaders->FileHeader.NumberOfSections;
	pSectionHeader = (PIMAGE_SECTION_HEADER)((DWORD)pNtHeaders+sizeof(IMAGE_NT_HEADERS));
    printf("\nIMAGE_SECTION_HEADER结构:\n");
	for(;dwSection < dwSectionCount;pSectionHeader++,dwSection++){
		printf("SECTION_HEADER#%d:\n",dwSection+1);
        printf("Name                    : %s\n",pSectionHeader->Name);
		printf("VirtualAddress          : %08x\n",pSectionHeader->VirtualAddress);
		printf("SizeOfRawData           : %08x\n",pSectionHeader->SizeOfRawData);
		printf("PointerToRawData        : %08x\n",pSectionHeader->PointerToRawData);
		printf("PointerToRelocations    : %08x\n",pSectionHeader->PointerToRelocations);
		printf("PointerToLinenumbers    : %08x\n",pSectionHeader->PointerToLinenumbers);
		printf("NumberOfRelocations     : %04x\n",pSectionHeader->NumberOfRelocations);
		printf("NumberOfLinenumbers     : %04x\n",pSectionHeader->NumberOfLinenumbers);
		printf("Characteristics         : %08x\n",pSectionHeader->Characteristics);
    }

	/**********END**********/
	UnmapViewOfFile(lpFile);
	CloseHandle(hFileMap);
	CloseHandle(hFile);
	return 0;
}

int GetPeImportTable(char*path)
{
	/**********START**********/
	HANDLE hFile,hFileMap;
	OFSTRUCT OpenBuff;
	DWORD dwImportDirectoryVA,dwSectionCount,dwSection=0,dwRawOffset;
	LPVOID lpFile;
	PIMAGE_DOS_HEADER pDosHeader;
	PIMAGE_NT_HEADERS pNtHeaders;
	PIMAGE_SECTION_HEADER pSectionHeader;
	PIMAGE_IMPORT_DESCRIPTOR pImportDescriptor;
	PIMAGE_THUNK_DATA pThunkData;

	/**********打开PE文件**********/
	hFile = (HANDLE)OpenFile(
		path,
		&OpenBuff,
		OF_READ
		);
	printf("Dump of file %s:\n",path);
	if(hFile==INVALID_HANDLE_VALUE)
		return -1;
	hFileMap = CreateFileMapping(
		hFile,
		0,
		PAGE_READONLY,
		0,
		0,
		0
		);

	lpFile = MapViewOfFile(
		hFileMap,
		FILE_MAP_READ,
		0,
		0,
		0
		);

	/**********判断是否为PE文件并显示PE文件格式**********/
	pDosHeader = (PIMAGE_DOS_HEADER)lpFile;
	pNtHeaders = (PIMAGE_NT_HEADERS)((DWORD)lpFile+pDosHeader->e_lfanew);
	if((pDosHeader->e_magic ==IMAGE_DOS_SIGNATURE)&&(pNtHeaders->Signature== IMAGE_NT_SIGNATURE)) 
		printf("有效的PE文件\n");
	else
		printf("无效的PE文件\n");
	PrintPeFileFormat(pNtHeaders->FileHeader.Characteristics);
	/**********IMAGE_IMPORT_DERECTORY**********/
	pSectionHeader = (PIMAGE_SECTION_HEADER)((DWORD)pNtHeaders+sizeof(IMAGE_NT_HEADERS));
	dwSectionCount = pNtHeaders->FileHeader.NumberOfSections;
	dwImportDirectoryVA = pNtHeaders->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress;
	if(dwImportDirectoryVA){
		printf("Section contains the following imports:\n");
		for(;dwSection < dwSectionCount && pSectionHeader->VirtualAddress <= dwImportDirectoryVA;pSectionHeader++,dwSection++);
		pSectionHeader--;
		dwRawOffset = (DWORD)lpFile+pSectionHeader->PointerToRawData-pSectionHeader->VirtualAddress;
		pImportDescriptor = (PIMAGE_IMPORT_DESCRIPTOR)(dwRawOffset+dwImportDirectoryVA);
		for(;pImportDescriptor->Name!=0;pImportDescriptor++)
		{
			printf("\nDLL Name: %s\n",dwRawOffset+pImportDescriptor->Name);
			pThunkData = (PIMAGE_THUNK_DATA)(dwRawOffset+pImportDescriptor->FirstThunk);
			for(;pThunkData->u1.AddressOfData != 0;pThunkData++){
				printf("Function: %s\n",(dwRawOffset+pThunkData->u1.Function+2));
			}
		}
	}
	else
		printf("\nSection has no imports.\n");
	/**********END**********/
	UnmapViewOfFile(lpFile);
	CloseHandle(hFileMap);
	CloseHandle(hFile);
	return 0;
}

int GetPeExportTable(char*path)
{
	/**********START**********/
	HANDLE hFile,hFileMap;
	OFSTRUCT OpenBuff;
	DWORD dwExportDirectoryVA,dwSectionCount,dwSection,dwRawOffset;
	LPVOID lpFile;
	PIMAGE_DOS_HEADER pDosHeader;
	PIMAGE_NT_HEADERS pNtHeaders;
	PIMAGE_SECTION_HEADER pSectionHeader;
	PIMAGE_EXPORT_DIRECTORY pExportDirectory;
	/**********打开PE文件**********/
	hFile = (HANDLE)OpenFile(
		path,
		&OpenBuff,
		OF_READ
		);

	printf("Dump of file %s:\n",path);
	if(hFile==INVALID_HANDLE_VALUE)
		return -1;
	hFileMap = CreateFileMapping(
		hFile,
		0,
		PAGE_READONLY,
		0,
		0,
		0
		);

	lpFile = MapViewOfFile(
		hFileMap,
		FILE_MAP_READ,
		0,
		0,
		0
		);

	/**********判断是否为PE文件并显示PE文件格式**********/
	pDosHeader = (PIMAGE_DOS_HEADER)lpFile;
	pNtHeaders = (PIMAGE_NT_HEADERS)((DWORD)lpFile+pDosHeader->e_lfanew);
	if((pDosHeader->e_magic ==IMAGE_DOS_SIGNATURE)&&(pNtHeaders->Signature== IMAGE_NT_SIGNATURE)) 
		printf("有效的PE文件\n");
	else
		printf("无效的PE文件\n");
	PrintPeFileFormat(pNtHeaders->FileHeader.Characteristics);

	/**********IMAGE_EXPORT_DERECTORY**********/
	dwExportDirectoryVA = pNtHeaders->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress;
	if(dwExportDirectoryVA){
		printf("\nSection contains the following exports:\n");
		pSectionHeader = (PIMAGE_SECTION_HEADER)((DWORD)pNtHeaders+sizeof(IMAGE_NT_HEADERS));
		dwSectionCount = pNtHeaders->FileHeader.NumberOfSections;
		for(;dwSection < dwSectionCount && pSectionHeader->VirtualAddress <= dwExportDirectoryVA;pSectionHeader++,dwSection++);
		pSectionHeader--;
		dwRawOffset = (DWORD)lpFile+pSectionHeader->PointerToRawData-pSectionHeader->VirtualAddress;
		pExportDirectory=(PIMAGE_EXPORT_DIRECTORY)(dwRawOffset+dwExportDirectoryVA);
		printf("Name: %s\n",dwRawOffset+pExportDirectory->Name);
		printf("NumberOfFunctions: %d\n",pExportDirectory->NumberOfFunctions);
		printf("NumberOfNames: %d\n",pExportDirectory->NumberOfNames);
		if (pExportDirectory->AddressOfNames != NULL && pExportDirectory->AddressOfFunctions != NULL)
		{
			PVOID names = (BYTE*)(dwRawOffset+pExportDirectory->AddressOfNames);
			PVOID funcs = (BYTE*)(dwRawOffset+pExportDirectory->AddressOfFunctions);
			for (DWORD i = 0; i < pExportDirectory->NumberOfNames; i++)
				printf("%d %s\n",i+1,dwRawOffset+((DWORD*)names)[i]);
		}
	}
	else
		printf("\nSection has no exports.\n");
	/**********END**********/
	UnmapViewOfFile(lpFile);
	CloseHandle(hFileMap);
	CloseHandle(hFile);
	return 0;
}

int GetPeTable(char*path)
{
	/**********START**********/
	HANDLE hFile,hFileMap;
	OFSTRUCT OpenBuff;
	DWORD dwImportDirectoryVA,dwExportDirectoryVA,dwSectionCount,dwSection=0,dwRawOffset;
	LPVOID lpFile;
	PIMAGE_DOS_HEADER pDosHeader;
	PIMAGE_NT_HEADERS pNtHeaders;
	PIMAGE_SECTION_HEADER pImSectionHeader;
	PIMAGE_SECTION_HEADER pExSectionHeader;
	PIMAGE_IMPORT_DESCRIPTOR pImportDescriptor;
	PIMAGE_THUNK_DATA pThunkData;
	PIMAGE_EXPORT_DIRECTORY pExportDirectory;
	/**********打开PE文件**********/
	hFile = (HANDLE)OpenFile(
		path,
		&OpenBuff,
		OF_READ
		);

	printf("Dump of file %s:\n",path);

	if(hFile==INVALID_HANDLE_VALUE)
		return -1;

	hFileMap = CreateFileMapping(
		hFile,
		0,
		PAGE_READONLY,
		0,
		0,
		0
		);

	lpFile = MapViewOfFile(
		hFileMap,
		FILE_MAP_READ,
		0,
		0,
		0
		);

	/**********判断是否为PE文件并显示PE文件格式**********/
	pDosHeader = (PIMAGE_DOS_HEADER)lpFile;
	pNtHeaders = (PIMAGE_NT_HEADERS)((DWORD)lpFile+pDosHeader->e_lfanew);
	if((pDosHeader->e_magic ==IMAGE_DOS_SIGNATURE)&&(pNtHeaders->Signature== IMAGE_NT_SIGNATURE)) 
		printf("有效的PE文件\n");
	else
		printf("无效的PE文件\n");
	PrintPeFileFormat(pNtHeaders->FileHeader.Characteristics);
	
	pImSectionHeader = pExSectionHeader = (PIMAGE_SECTION_HEADER)((DWORD)pNtHeaders+sizeof(IMAGE_NT_HEADERS));
	dwSectionCount = pNtHeaders->FileHeader.NumberOfSections;
	/**********IMAGE_IMPORT_DERECTORY**********/
	dwImportDirectoryVA = pNtHeaders->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress;
	if(dwImportDirectoryVA){
		printf("\nSection contains the following imports:\n");
		for(dwSection=0;dwSection < dwSectionCount && pImSectionHeader->VirtualAddress <= dwImportDirectoryVA;pImSectionHeader++,dwSection++);
		pImSectionHeader--;
		dwRawOffset = (DWORD)lpFile+pImSectionHeader->PointerToRawData-pImSectionHeader->VirtualAddress;
		pImportDescriptor = (PIMAGE_IMPORT_DESCRIPTOR)(dwRawOffset+dwImportDirectoryVA);
		for(;pImportDescriptor->Name!=0;pImportDescriptor++)
		{
			printf("\nDLL Name: %s\n",dwRawOffset+pImportDescriptor->Name);
			pThunkData = (PIMAGE_THUNK_DATA)(dwRawOffset+pImportDescriptor->FirstThunk);
			for(;pThunkData->u1.AddressOfData != 0;pThunkData++){
				if(pThunkData->u1.Function&0x80000000)               //如果越界
					break;
				printf("Function: %s\n",(dwRawOffset+pThunkData->u1.Function+2));
			}
		}
	}
	else
		printf("\nSection has no imports.\n");

	/**********IMAGE_EXPORT_DERECTORY**********/
	dwExportDirectoryVA = pNtHeaders->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress;
	if(dwExportDirectoryVA){
		printf("\nSection contains the following exports:\n");
		for(dwSection=0;dwSection < dwSectionCount && pExSectionHeader->VirtualAddress <= dwExportDirectoryVA;pExSectionHeader++,dwSection++);
		pExSectionHeader--;
		dwRawOffset = (DWORD)lpFile+pExSectionHeader->PointerToRawData-pExSectionHeader->VirtualAddress;
		pExportDirectory=(PIMAGE_EXPORT_DIRECTORY)(dwRawOffset+dwExportDirectoryVA);
		printf("Name: %s\n",dwRawOffset+pExportDirectory->Name);
		printf("NumberOfFunctions: %d\n",pExportDirectory->NumberOfFunctions);
		printf("NumberOfNames: %d\n",pExportDirectory->NumberOfNames);
		if (pExportDirectory->AddressOfNames != NULL && pExportDirectory->AddressOfFunctions != NULL)
		{
			PVOID names = (BYTE*)(dwRawOffset+pExportDirectory->AddressOfNames);
			PVOID funcs = (BYTE*)(dwRawOffset+pExportDirectory->AddressOfFunctions);
			for (DWORD i = 0; i < pExportDirectory->NumberOfNames; i++)
				printf("%d %s\n",i+1,dwRawOffset+((DWORD*)names)[i]);
		}
	}
	else
		printf("\nSection has no exports.\n");

	/**********END**********/
	UnmapViewOfFile(lpFile);
	CloseHandle(hFileMap);
	CloseHandle(hFile);
	return 0;
}

/*
int GetPeImportTable0(char*path){
	printf("Dump of file %s:\n",path);
	HMODULE module = LoadLibrary(path);
	if(module==NULL)
		return -1;
    PIMAGE_NT_HEADERS header = (PIMAGE_NT_HEADERS)((BYTE *)module + ((PIMAGE_DOS_HEADER)module)->e_lfanew);
    PIMAGE_IMPORT_DESCRIPTOR imports = (PIMAGE_IMPORT_DESCRIPTOR)((BYTE*)module + header->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress);
	PIMAGE_THUNK_DATA pThunkData;
	printf("Section contains the following imports:\n");
	for(;imports->Name!=0;imports++)
	{
		printf("DLL Name: %s\n",(BYTE*) module+imports->Name);
		pThunkData = (PIMAGE_THUNK_DATA)((BYTE*) module+imports->FirstThunk);
		for(;pThunkData->u1.AddressOfData != 0;pThunkData++)
			printf("Function: %s\n",((BYTE*) module+pThunkData->u1.Function+2));
	}
	if(FreeLibrary(module)==0)
		return -2;
    return 0;
}

int GetPeExportTable0(char*path) {
	printf("Dump of file %s:\n",path);
	HMODULE module = LoadLibrary(path);
	if(module==NULL)
		return -1;
    PIMAGE_NT_HEADERS header = (PIMAGE_NT_HEADERS)((BYTE *)module + ((PIMAGE_DOS_HEADER)module)->e_lfanew);
    PIMAGE_EXPORT_DIRECTORY exports = (PIMAGE_EXPORT_DIRECTORY)((BYTE*)module + header->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress);
	
	printf("Section contains the following exports:\n");
	if (exports->AddressOfNames != NULL && exports->AddressOfFunctions != NULL)
	{
		PVOID names = (BYTE*) module + exports->AddressOfNames;
		PVOID funcs = (BYTE*) module + exports->AddressOfFunctions;

		for(DWORD i = 0;i < exports->NumberOfNames;i++){
			char* name = (char*)((BYTE*) module + ((DWORD*) names)[i]);
			printf("%d %s\n",i+1,name);
		}
	}
	if(FreeLibrary(module)==0)
		return -2;
    return 0;
}*/