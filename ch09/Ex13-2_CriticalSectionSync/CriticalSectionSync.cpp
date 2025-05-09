/*
CriticalSectionSync.cpp
���α׷� ���� : �Ӱ� ���� ��� ����ȭ �ǽ�
*/

#include <stdio.h>
#include <tchar.h>
#include <process.h>
#include <Windows.h>

#define NUM_OF_GATE 6

LONG gTotalCount = 0;	// ��� �����尡 gTotalCount�� ������

CRITICAL_SECTION hCriticalSection;	// �Ӱ� ���� ������ ���� ������ ����, �������� �������� ID ���� ���� ���� �ִ� ����ü

/* gTotalCount ���� �а�, 1�� ���� �� �ٽ� �޸𸮿� ���� �Լ� **/
void IncreaseCount() {
	EnterCriticalSection(&hCriticalSection);
	gTotalCount++; // �Ӱ� ���� (Critical Section)
	LeaveCriticalSection(&hCriticalSection);
}

unsigned int WINAPI ThreadProc(LPVOID lpParam) {
	// �� �����带 1�� 10,000�� ����, �����尡 6���̱⿡ 60,000�� �Ǿ�� ��
	for (DWORD i = 0; i < 10000; i++) {
		IncreaseCount();
	}
	return 0;
}

int _tmain(int argc, TCHAR* argv[]) {
	DWORD dwThreadId[NUM_OF_GATE];	// 6���� ������ ����
	HANDLE hThread[NUM_OF_GATE];

	InitializeCriticalSection(&hCriticalSection);	// �׻� ���� ���� �ʱ�ȭ ���� �ؾ���

	/** 6���� ������ �����ϴ� for�� */
	/** suspend ���·� �����Ǿ�, ������ ������ */
	for (DWORD i = 0; i < NUM_OF_GATE; i++) {
		hThread[i] = (HANDLE)_beginthreadex(NULL, 0, ThreadProc, NULL, CREATE_SUSPENDED, (unsigned*)&dwThreadId[i]);

		if (hThread[i] == NULL) {
			_tprintf(_T("Thread creation fault!\n"));
			return -1;
		}
	}

	for (DWORD i = 0; i < NUM_OF_GATE; i++) {
		ResumeThread(hThread[i]);	// ResumThread() ȣ�� ���� ������ ����, ����ȭ ���� ������ ������ ����
	}

	WaitForMultipleObjects(NUM_OF_GATE, hThread, TRUE, INFINITE);

	_tprintf(_T("total count : %d \n"), gTotalCount);

	for (DWORD i = 0; i < NUM_OF_GATE; i++) {
		CloseHandle(hThread[i]);
	}

	DeleteCriticalSection(&hCriticalSection);	// �� �� �Ŀ��� ������ ���Ͽ� �޸� ���� ����
	return 0;
}