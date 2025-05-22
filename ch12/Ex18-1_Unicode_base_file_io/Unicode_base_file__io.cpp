#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

int _tmain(int argc, TCHAR* argv[])
{
	TCHAR fileName[] = _T("data.txt");
	TCHAR fileData[] = _T("Just test string~");

	HANDLE hFile = CreateFile(fileName, GENERIC_WRITE, FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hFile == INVALID_HANDLE_VALUE) {
		_tprintf(_T("File creation fault! \n"));
		return -1;
	}

	DWORD numOfBytesWritten = 0;
	
	WriteFile(hFile, fileData, sizeof(fileData), &numOfBytesWritten, NULL);
	_tprintf(_T("Written data size : %d \n"), numOfBytesWritten);
	
	CloseHandle(hFile);
	return 0;
}