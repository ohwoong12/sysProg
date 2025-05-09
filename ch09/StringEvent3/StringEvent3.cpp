/*
StringEvent3.cpp
���α׷� ���� : event, mutex ���� ��� ���
*/
#include <stdio.h>
#include <tchar.h>
#include <windows.h>
#include <process.h> // _beginthreadex, _endthreadex

unsigned int WINAPI OutputThreadFunction(LPVOID lpParam);
unsigned int WINAPI CountThreadFunction(LPVOID lpParam);

typedef struct _SyncString {
	TCHAR string[100];
	HANDLE hEvent;
	HANDLE hMutex;
} SyncString;

SyncString gSyncString;

int _tmain(int argc, TCHAR* argv[]) {
	HANDLE hThread[2];
	DWORD dwThreadID[2];

	gSyncString.hEvent = CreateEvent(
		NULL, // default ���ȼ�����, ��ӺҰ�
		TRUE, // manual-reset mode�� ����
		FALSE,// non-signaled ���·� ����
		NULL // �̸����� event
	);

	gSyncString.hMutex = CreateMutex(NULL, FALSE, NULL);

	if (gSyncString.hEvent == NULL || gSyncString.hMutex == NULL) {
		_fputts(_T("kernel object creation error \n"), stdout);
		return -1;
	}

	hThread[0] = (HANDLE)_beginthreadex(
		NULL, 0, // �⺻ ���� �Ӽ�, �⺻ ���� ũ�� ����
		OutputThreadFunction,
		NULL,0,
		(unsigned*)&dwThreadID
	);

	hThread[1] = (HANDLE)_beginthreadex(
		NULL, 0,
		CountThreadFunction,
		NULL, 0,
		(unsigned*)&dwThreadID);

	if (hThread[0] == 0 || hThread[1] == NULL) {
		_fputts(_T("Thread creation error \n"), stdout);
		return -1;
	}

	_fputts(_T("Insert string: "), stdout);
	_fgetts(gSyncString.string, 50, stdin);

	SetEvent(gSyncString.hEvent); // event�� state�� signaled ���·� ���� (event ���� ���� ��ȣ)

	WaitForMultipleObjects(
		2, // �迭�� ����, �ΰ� thread
		hThread, // �ڵ� �迭�� �ּ�
		TRUE, // ��� �ڵ��� ��ȣ���� ���·� �� �� ����
		INFINITE);

	CloseHandle(gSyncString.hEvent);
	CloseHandle(gSyncString.hMutex);
	CloseHandle(hThread[0]);
	CloseHandle(hThread[1]);

	return 0;
}
unsigned int WINAPI OutputThreadFunction(LPVOID lpParam) {
	// event�� signaled ���°� �Ǳ⸦ ��ٸ���.
	WaitForSingleObject(gSyncString.hEvent, INFINITE);
	WaitForSingleObject(gSyncString.hMutex, INFINITE);

	_fputts(_T("Output string: "), stdout);
	_fputts(gSyncString.string, stdout);
	_fputts(_T(" \n"), stdout);

	ReleaseMutex(gSyncString.hMutex);

	return 0;
}
unsigned int WINAPI CountThreadFunction(LPVOID lpParam)
{
	// event�� signaled ���°� �Ǳ⸦ ��ٸ���.
	WaitForSingleObject(gSyncString.hEvent, INFINITE);
	WaitForSingleObject(gSyncString.hMutex, INFINITE);

	_tprintf(_T("Output string length : %d \n"),
	_tcslen(gSyncString.string) - 1); // string���� ���� �ִ� NULL ���ڴ� ����

	ReleaseMutex(gSyncString.hMutex);

	return 0;
}
