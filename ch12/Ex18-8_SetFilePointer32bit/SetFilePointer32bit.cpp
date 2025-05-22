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

	// file write (신규 파일 abcd.txt open, 파일에 fileData배열 내용 쓰기)
	hFile = CreateFile(fileName, GENERIC_WRITE, 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
	WriteFile(hFile, fileData, sizeof(fileData), &numOfByteWritten, NULL);
	_tprintf(_T("number of bytes written : %d\n"), numOfByteWritten);
	
	CloseHandle(hFile);

	// file read (abcd.txt 파일 열고, 읽고, 화면에 출력)
	hFile = CreateFile(fileName, GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	ReadFile(hFile, readBuf, sizeof(readBuf), &numOfByteWritten, NULL);
	_tprintf(_T("\n%s \n"), readBuf);
	_tprintf(_T("number of bytes read : %d\n"), numOfByteWritten);	
	// 파일 포인터를 맨 앞에서 4bytes 이동
	dwPtr = SetFilePointer(hFile, sizeof(TCHAR) * 4, NULL, FILE_BEGIN);
	if (dwPtr == INVALID_SET_FILE_POINTER) {
		_tprintf(_T("SetFilePointer error \n"));
		return -1;
	}

	ReadFile(hFile, readBuf, sizeof(readBuf), &numOfByteWritten, NULL);
	_tprintf(_T("\n%s \n"), readBuf);
	_tprintf(_T("number of bytes read : %d\n"), numOfByteWritten);
	
	// 파일 포인터를 맨 뒤에서 앞으로 4bytes 이동
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