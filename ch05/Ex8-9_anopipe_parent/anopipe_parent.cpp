/* anonymous pipe�� ���� ���� ���μ��� �� ����� �ƴ�,
���� �ٸ� �� ���μ�����(�θ�-�ڽ�) ��� �����ϱ�
anopipe_parent.cpp
���α׷� ����: �̸����� ������ �θ� ���μ���(������ ����, �������� �޼��� ����)
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <tchar.h>
#include <windows.h>
int _tmain(int argc, LPTSTR argv[])
{
	HANDLE hReadPipe, hWritePipe; //pipe handle
	TCHAR sendString[] = _T("anonymous pipe 2");
	DWORD bytesWritten;
	SECURITY_ATTRIBUTES sa;
	sa.nLength = sizeof(sa);
	sa.lpSecurityDescriptor = NULL;	// Pipe ����(CreatePipe)�� �ڵ� ��� ����(bInheritHandles = TRUE)���� ����
	sa.bInheritHandle = TRUE; 
	/*
	anopipe_child.exe�� anopipe_parent ���μ������� CreatProcess() �Լ��� �����Ͽ� ��� �� ��.
	�̶� child procces�� anopipe_child�� hReadPipe�� �ڵ� ����(�ڵ� ��ȣ�� �׿� �ش��ϴ� �ּ�)�� �˰� �־�� �ùٸ��� ���� ��.
	��, �ڵ� ������ ��ӹ޾ƾ� �ùٸ� �ּҿ��� �޽����� �о� �� �� ����.
	�̰��� Pipe�� ��� ������ �ڵ�� �����ϴ� ����
	*/
	//pipe ����
	CreatePipe(&hReadPipe, &hWritePipe, &sa, 0); // Pipe�� ��� ����(Y) �ڵ�� ����
	//pipe�� ���� ���� �̿��� ������ �۽�
	WriteFile(hWritePipe, sendString, _tcslen(sendString) * sizeof(TCHAR), &bytesWritten, NULL);
	_tprintf(_T("string send: %s, written in bytes : %d \n"), sendString, bytesWritten);
	TCHAR command[1024];
	//command line���� handle ���� �����ϱ�
	_stprintf(command, _T("%s %u %u"), _T("Ex8-9_anopipe_child.exe"), (unsigned)hReadPipe, bytesWritten);
	_tprintf(_T("hReadPipe: %d \n"), (unsigned)hReadPipe);


	STARTUPINFO si = { 0, };
	PROCESS_INFORMATION pi;
	si.cb = sizeof(si);
	BOOL state;
	state = CreateProcess(NULL, command, NULL, NULL, TRUE, CREATE_NEW_CONSOLE | NORMAL_PRIORITY_CLASS, NULL, NULL, &si, &pi);
	if (state == 0) {
		_fputts(_T("file creation failed\n"), stdout);
	}
	else {
		_fputts(_T("file creation success\n"), stdout);
	}

	CloseHandle(hReadPipe);
	CloseHandle(hWritePipe);
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
	
	return 0;
}