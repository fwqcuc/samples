//#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

#define BUFFER_SIZE 128


BOOL FileSize(LPSTR szFilePath, LPDWORD dwSize)
{
	WIN32_FIND_DATA wfd;
	HANDLE  hFind = FindFirstFile(szFilePath, &wfd);

	if (hFind == INVALID_HANDLE_VALUE)
		return FALSE;

	if (wfd.nFileSizeHigh != 0)
		return FALSE;

	*dwSize = wfd.nFileSizeLow;

	FindClose(hFind);

	return TRUE;

}

DWORD LoadFile(LPSTR szFile, LPBYTE lpData, DWORD dwSize)
{
	DWORD dwBytesRead;
	HANDLE hFile = CreateFile(szFile, // open One.txt
		GENERIC_READ,             // open for reading
		FILE_SHARE_READ,                        // do not share
		NULL,          // no security
		OPEN_EXISTING,            // existing file only
		FILE_ATTRIBUTE_NORMAL,    // normal file
		NULL);                    // no attr. template

	if (hFile == INVALID_HANDLE_VALUE)
	{
		return 0;
	}

	if (!ReadFile(hFile, lpData, dwSize, &dwBytesRead, NULL))
	{
		printf("error(%d)", GetLastError());
		CloseHandle(hFile);
		return 0;
	}

	CloseHandle(hFile);
	return dwBytesRead;
}
DWORD dwFileSize;
int i;
int main(int argc, char** argv)
{
	char s[BUFFER_SIZE] = "null";

	if (argc != 2)
	{
		printf("usage :%s, file_path", argv[0]);
		return 0;
	}
	if (FileSize(argv[1], &dwFileSize))
	{

		LPBYTE lpData = malloc(dwFileSize);
		LoadFile(argv[1], lpData, dwFileSize);
		memcpy(s, lpData, dwFileSize);
	}
	else
		printf("file error(%d)", GetLastError());
	return 0;
}