#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

#define STRING_LEN 1024

int _tmain(int argc, TCHAR* argv[])
{
	TCHAR fileName[] = _T("data.txt");
	TCHAR fileData[STRING_LEN];

	HANDLE hFile = CreateFile(fileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE) {
		_tprintf(_T("File open failed! \n"));
		return -1;
	}

	DWORD numOfBytesRead = 0;

	ReadFile(hFile, fileData, sizeof(fileData), &numOfBytesRead, NULL);
	fileData[numOfBytesRead / sizeof(TCHAR)] = '\0';//string 마지막NULL처리
	_tprintf(_T("Read data size : %d \n"), numOfBytesRead);
	_tprintf(_T("%s\n"), fileData);

	CloseHandle(hFile);
	return 0;
}