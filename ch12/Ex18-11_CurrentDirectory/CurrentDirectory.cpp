#include <stdio.h>
#include <tchar.h>
#include <windows.h>
#define STRING_LEN 100

TCHAR fileData[] = _T("abcdefghijklmnopqrstuvwxyz");

int _tmain(int argc, TCHAR* argv[])
{
	TCHAR fileName[] = _T("abc.txt");
	TCHAR readBuf[STRING_LEN];
	HANDLE hFileWrite;
	HANDLE hFileRead;
	DWORD numOfByteWritten;

	// 1. ���丮 ���� (�������� ������ ������)
	if(!CreateDirectory(_T("c:\\CmdTest\\"),NULL)){
		if (GetLastError() != ERROR_ALREADY_EXISTS) {
			_tprintf(_T("���丮 ���� ����: %d \n"), GetLastError());
			return -1;
		}
	}

	// 2. ���� ���丮 ����
	if (!SetCurrentDirectory(_T("c:\\CmdTest\\"))) {
		_tprintf(_T("�۾� ���丮 ���� ���� \n"));
		return -1;
	}

	/*
	// ���� ���͸� ����, ������ ���͸��� �������� ������ ���� (false ��ȯ)
	SetCurrentDirectory(_T("c:\\CmdTest\\"));
	*/

	// file write
	hFileWrite = CreateFile(fileName, GENERIC_WRITE, 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
	WriteFile(hFileWrite, fileData, sizeof(fileData), &numOfByteWritten, NULL);
	CloseHandle(hFileWrite);
	
	// file read
	hFileRead = CreateFile(fileName, GENERIC_READ, 0, 0, OPEN_EXISTING, 0, 0);
	if (hFileRead == INVALID_HANDLE_VALUE) {
		_tprintf(_T("file open failed! \n"));
		return -1;
	}
	ReadFile(hFileRead, readBuf, sizeof(readBuf), &numOfByteWritten, 0);
	_tprintf(_T("%s \n"), readBuf);
	
	CloseHandle(hFileRead);
	return 0;
}