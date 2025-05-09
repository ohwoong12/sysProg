#include <stdio.h>
#include <tchar.h>
#include <time.h>
#include <windows.h>
#include <process.h>

#define NUM_OF_CUSTOMER 50			// �մ� ��
#define RANGE_MIN 10				// �ּ� �Ļ� �ð�
#define RANGE_MAX (30 - RANGE_MIN)	// �Ļ� �ð� ����
#define TABLE_CNT 10				// ��Ź ���� = �������� �ʱⰪ

CRITICAL_SECTION gElapsedTimeLock;	// �Ӱ� ������ ���� ��ü
HANDLE hSemaphore;					// ��Ź �� ��ŭ�� ���� ������ �����ϴ� �������� ��ü (���� ���� ���ѿ�)
DWORD randTimeArr[50];				// �մ� 50���� ���� �Ļ� �ð��� ������ �迭
DWORD gElapsedTime = 0;				// ��ü �մԵ��� �Ļ� �ð� ������ (���� �ڿ��̱⿡ Crtical Section ���)

void TakeMeal(DWORD time) {
	DWORD thID = GetCurrentThreadId();	// ���� �������� ID ��������

	WaitForSingleObject(hSemaphore, INFINITE);	// �ڿ��� �ִٸ� ��������, ���ٸ� ���Ѵ��

	_tprintf(_T("Enter Customer %d~ \n"), thID);
	_tprintf(_T("Customer %d having launch~\n\n"), thID);

	Sleep(100 * time); // �Ļ� �ð� ���� ���

	EnterCriticalSection(&gElapsedTimeLock);	// �Ӱ� ���� ����
	gElapsedTime += time;	//�Ļ� �ð� ����
	_tprintf(_T("Elapsed time for customer No. %d is %d \n"), thID, time);
	_tprintf(_T("Total serving time(minutes) is %d \n"), gElapsedTime);
	LeaveCriticalSection(&gElapsedTimeLock);	// �Ӱ� ���� ��Ż

	ReleaseSemaphore(hSemaphore, 1, NULL);	// �ٸ� ������ ���� �����ϵ��� �������� �ڿ� �ݳ�
	_tprintf(_T("Out Customer %d \n\n"), thID);
}

unsigned int WINAPI ThreadProc(LPVOID lpParam) {
	TakeMeal((DWORD)lpParam);	// �Ű������� ���� �Ļ� �ð� �����Ͽ� �Ļ� ����
	return 0;	// ������ ����
}

int _tmain(int argc, TCHAR* argv[]) {
	DWORD dwThreadId[NUM_OF_CUSTOMER];	// ������ ID ����� �迭
	HANDLE hThread[NUM_OF_CUSTOMER];	// ������ �ڵ� ����� �迭

	srand((unsigned)time(NULL)); // �̾����� rand()�Լ� ȣ�⿡ ���� seed ����

	// �����忡 ������ random�� �� 50�� ����
	for (int i = 0; i < NUM_OF_CUSTOMER; i++) {
			randTimeArr[i] = (DWORD)(((double)rand() / (double)RAND_MAX) *
				RANGE_MAX + RANGE_MIN);
	}	// �մ� ����ŭ ���� �Ļ� �ð� ���� (10 ~ 30 ����)

	InitializeCriticalSection(&gElapsedTimeLock);	// �Ӱ� ���� �ʱ�ȭ (�ʼ�)
	
	hSemaphore = CreateSemaphore(NULL, TABLE_CNT, TABLE_CNT, NULL);	// �������� ���� (�ִ� TABLE_CNT�� ���� ���� ���� ����)

	if (hSemaphore == NULL)
		_tprintf(_T("Create Semaphore failed, error code is %d \n"), GetLastError());

	// Customer�� �ǹ��ϴ� ������ ����
	for (int i = 0; i < NUM_OF_CUSTOMER; i++) {
		hThread[i] = (HANDLE)_beginthreadex( NULL, 0, ThreadProc, (void*)randTimeArr[i], CREATE_SUSPENDED, (unsigned*)&dwThreadId[i]);

		if (hThread[i] == NULL) {
			_tprintf(_T("Thread creation failed! \n"));
			return -1;
		}
	}

	for (int i = 0; i < NUM_OF_CUSTOMER; i++) {
		ResumeThread(hThread[i]);
	}

	// MAXIMUM_WAIT_OBJECTS�� 64�� 64�� �̻��� customer�� ���� �Ұ�
	//WaitForMultipleObjects(NUM_OF_CUSTOMER, hThread, TRUE, INFINITE);
	
	// MAXIMUM_WAIT_OBJECTS�� 64 �ذ� ����....
	for (int i = 0; i < NUM_OF_CUSTOMER; i++) {
		WaitForSingleObject(hThread[i], INFINITE);
	}

	_tprintf(_T("--- End --- \n"));

	for (int i = 0; i < NUM_OF_CUSTOMER; i++)
		CloseHandle(hThread[i]);

	CloseHandle(hSemaphore);
	return 0;
}
