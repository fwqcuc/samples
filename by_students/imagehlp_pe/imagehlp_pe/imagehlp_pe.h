#include<Windows.h>
#include<stdio.h>

void PrintPeFileFormat(WORD Characteristics);
int GetPeHeaders(char*path);
int GetPeTable(char*path);
int GetPeImportTable(char*path);
int GetPeExportTable(char*path);

/*
int GetPeImportTable0(char*path);
int GetPeExportTable0(char*path);
int GetPeFormat(char*path);
*/