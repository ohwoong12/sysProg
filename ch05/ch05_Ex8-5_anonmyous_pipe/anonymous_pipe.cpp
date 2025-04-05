#include<stdio.h>
#include<tchar.h>
#include<Windows.h>

int _tmain(int argc, TCHAR* argv[]) {
	HANDLE hReadPipe, hWritePipe;	//pipe handle

	TCHAR sendString[] = _T("anonymous pipe");
	TCHAR recvString[100];

	DWORD bytesWritten;
	DWORD bytesRead;

	//pipe ����
	CreatePipe(&hReadPipe, &hWritePipe, NULL, 0);
	
	//pipe�� ���� ���� �̿��� ������ �۽�
	WriteFile(hWritePipe, sendString, _tcslen(sendString) * sizeof(TCHAR), &bytesWritten, NULL);
	_tprintf(_T("string send: %s \n"), sendString);

	//pipe�� ���� ���� �̿��� ������ ����
	ReadFile(hReadPipe, recvString, bytesWritten, &bytesRead, NULL);
	recvString[bytesRead / sizeof(TCHAR)] = 0;
	_tprintf(_T("string recv: %s \n"), recvString);

	CloseHandle(hReadPipe);
	CloseHandle(hWritePipe);

	return 0;
}