/*
SuspendCount.cpp
���α׷� ���� : �������� ���� ����
*/
#include <stdio.h>
#include <tchar.h>
#include <windows.h>
#include <process.h>

unsigned int WINAPI ThreadProc(LPVOID lpParam) {
	int cnt = 0;

	while (1) {
		_tprintf(_T("Running State! \n"));
		Sleep(1000); // 1�� ���
		cnt++;
		if (cnt > 10) break; // 10ȸ ��� �� ����
	}
	return 0;
}


int _tmain(int argc, TCHAR* argv[]) {
	DWORD dwThreadId;
	HANDLE hThread;
	DWORD susCnt; // suspend count�� Ȯ���ϱ� ���� ����
	hThread = (HANDLE)_beginthreadex(NULL, 0, ThreadProc, NULL, CREATE_SUSPENDED, (unsigned*)&dwThreadId);

	// ������ ���� Ȯ��
	if (hThread == NULL)
		_tprintf(_T("Thread creation failed! \n"));

	susCnt = ResumeThread(hThread);
	_tprintf(_T("suspend count: %d \n"), susCnt);
	Sleep(1000);

	susCnt = SuspendThread(hThread);
	_tprintf(_T("suspend count: %d \n"), susCnt);
	Sleep(1000);

	susCnt = SuspendThread(hThread);
	_tprintf(_T("suspend count: %d \n"), susCnt); Sleep(1000);

	susCnt = ResumeThread(hThread);
	_tprintf(_T("suspend count: %d \n"), susCnt);

	susCnt = ResumeThread(hThread);
	_tprintf(_T("suspend count: %d \n"), susCnt);

	WaitForSingleObject(hThread, INFINITE);
	CloseHandle(hThread);
	return 0;
}