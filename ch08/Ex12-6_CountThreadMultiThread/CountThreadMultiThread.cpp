/*
CountThreadMultiThread.cpp
���α׷� ���� : _beginthreadex �Լ� ������� ����
*/
#include <stdio.h>
#include <tchar.h>
#include <process.h> // _beginthreadex ����
#include <windows.h>

#define MAX_THREADS (1024*10)

unsigned int WINAPI ThreadProc(LPVOID lpParam) {
	DWORD threadNum = (DWORD)lpParam;

	while (TRUE) {
		_tprintf(_T("thread num : %d \n"), threadNum);
		Sleep(1000);
	}
	return 0;
}

DWORD cntOfThread = 0;

int _tmain(int argc, TCHAR* argv[]) {
	DWORD dwThreadID[MAX_THREADS];
	HANDLE hThread[MAX_THREADS];

	// ���� ������ �ִ� ������ ������ ����
	while (TRUE) {
		hThread[cntOfThread] = (HANDLE)_beginthreadex(
			NULL,									// default ���� �Ӽ�
			1024 * 1024 * 100,						// stack size
			ThreadProc,								// thread �Լ�
			(LPVOID)cntOfThread,					// thread �Լ��� ��������(argument)
			0,										// default ���� flag ����
			(unsigned*)&dwThreadID[cntOfThread]);	// thread ID ��ȯ

		// ������ ���� Ȯ��
		if (hThread[cntOfThread] == NULL) {
			_tprintf(_T("MAXIMUM THREAD NUMBER : %d \n"),
				cntOfThread);
			break;
		}
		cntOfThread++;
	}

	for (DWORD i = 0; i < cntOfThread; i++) {
		CloseHandle(hThread[i]);
	}

	return 0;
}