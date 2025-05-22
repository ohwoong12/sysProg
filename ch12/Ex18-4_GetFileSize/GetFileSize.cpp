/*
GetFileSize.cpp
���α׷� ���� : ���� ũ�� ���� Ȯ���ϴ� ����
*/

#include <stdio.h>
#include <tchar.h>
#include <windows.h>

int _tmain(int argc, TCHAR* argv[])
{
	TCHAR fileName[] = _T("���� ������Ʈ.txt");
	HANDLE hFile = CreateFile(fileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	if (hFile == INVALID_HANDLE_VALUE) {
		_tprintf(_T("File open failed! \n"));
		return -1;
	}

	DWORD high4ByteFileSize = 0;
	DWORD low4ByteFileSize = GetFileSize(hFile, &high4ByteFileSize);
	
	_tprintf(_T("high 4byte file size : %u bytes \n"), high4ByteFileSize);
	_tprintf(_T("low 4byte file size : %u bytes \n"), low4ByteFileSize);
	
	LARGE_INTEGER fileSize;
	GetFileSizeEx(hFile, &fileSize);
	_tprintf(_T("total file size : %llu bytes \n"), fileSize.QuadPart);
	
	CloseHandle(hFile);
	return 0;
}