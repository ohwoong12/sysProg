#include <stdio.h>
#include <tchar.h>
#include <windows.h>

#define STRING_LEN 100

TCHAR fileData[] = _T("abcdefghijklmnopqrstuvwxyz");

int _tmain(int argc, TCHAR* argv[])
{
	TCHAR fileName[] = _T("abcd.txt");
	TCHAR readBuf[STRING_LEN];
	HANDLE hFile;
	DWORD numOfByteWritten = 0;
	DWORD dwPtr = 0;

	// file write (�ű� ���� abcd.txt open, ���Ͽ� fileData�迭 ���� ����)
	hFile = CreateFile(fileName, GENERIC_WRITE, 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
	WriteFile(hFile, fileData, sizeof(fileData), &numOfByteWritten, NULL);
	_tprintf(_T("number of bytes written : %d\n"), numOfByteWritten);
	
	CloseHandle(hFile);

	// file read (abcd.txt ���� ����, �а�, ȭ�鿡 ���)
	hFile = CreateFile(fileName, GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	ReadFile(hFile, readBuf, sizeof(readBuf), &numOfByteWritten, NULL);
	_tprintf(_T("\n%s \n"), readBuf);
	_tprintf(_T("number of bytes read : %d\n"), numOfByteWritten);	
	// ���� �����͸� �� �տ��� 4bytes �̵�
	dwPtr = SetFilePointer(hFile, sizeof(TCHAR) * 4, NULL, FILE_BEGIN);
	if (dwPtr == INVALID_SET_FILE_POINTER) {
		_tprintf(_T("SetFilePointer error \n"));
		return -1;
	}

	ReadFile(hFile, readBuf, sizeof(readBuf), &numOfByteWritten, NULL);
	_tprintf(_T("\n%s \n"), readBuf);
	_tprintf(_T("number of bytes read : %d\n"), numOfByteWritten);
	
	// ���� �����͸� �� �ڿ��� ������ 4bytes �̵�
	LONG step = sizeof(TCHAR) * 4;
	step = step * -1;
	
	dwPtr = SetFilePointer(hFile, step, NULL, FILE_END);
	if (dwPtr == INVALID_SET_FILE_POINTER) {
		_tprintf(_T("SetFilePointer error \n"));
		return -1;
	
	}
	ReadFile(hFile, readBuf, sizeof(readBuf), &numOfByteWritten, NULL);
	_tprintf(_T("\n%s \n"), readBuf);
	_tprintf(_T("number of bytes read : %d\n"), numOfByteWritten);
	
	CloseHandle(hFile);
	return 0;
}