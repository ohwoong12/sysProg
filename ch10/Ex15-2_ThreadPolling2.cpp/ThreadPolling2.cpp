#include <stdio.h>
#include <tchar.h>
#include <windows.h>

#define WORK_MAX 10000
#define THREAD_MAX 50

typedef void (*WORK)(void);


// ���� ������ ���� �� ����
typedef struct __WorkThread {
	HANDLE hThread;
	DWORD idThread;
} WorkerThread;

struct __ThreadPool {
	WORK workList[WORK_MAX];
	WorkerThread workerThreadList[THREAD_MAX];
	HANDLE workerEventList[THREAD_MAX];
	DWORD idxOfCurrentWork;
	DWORD idxOfLastAddedWork;
	DWORD threadIdx;
} gThreadPool;

static HANDLE mutex = NULL;
volatile BOOL gShutdown = FALSE;

// ------------------------------
// Mutex �Լ�
// ���� ������ gThreadPool�� ���� ���� ������ ����(����ȭ) ���� ����
// ------------------------------
void InitMutex(void) {
	mutex = CreateMutex(NULL, FALSE, NULL);
}
void DeInitMutex(void) {
	if (mutex) CloseHandle(mutex);
}
void AcquireMutex(void) {
	DWORD ret = WaitForSingleObject(mutex, INFINITE);
	if (ret == WAIT_FAILED)
		_tprintf(_T("Error occurred in AcquireMutex()\n"));
}
void ReleaseMutex(void) {
	if (!ReleaseMutex(mutex))
		_tprintf(_T("Error occurred in ReleaseMutex()\n"));
}

// Work ���/��ȸ
DWORD AddWorkToPool(WORK work) {
	AcquireMutex();
	
	if (gThreadPool.idxOfLastAddedWork >= WORK_MAX) {
		_tprintf(_T("AddWorkToPool failed!\n"));
		ReleaseMutex();
		return -1;
	}

	// work ���
	gThreadPool.workList[gThreadPool.idxOfLastAddedWork++] = work;

	// ��� ������ �̺�Ʈ ��ȣȭ (signaled�� ����)
	for (DWORD i = 0; i < gThreadPool.threadIdx; i++)
		SetEvent(gThreadPool.workerEventList[i]);

	ReleaseMutex();

	return 0;
}
WORK GetWorkFromPool() {
	WORK work = NULL;

	AcquireMutex();

	if (gThreadPool.idxOfCurrentWork < gThreadPool.idxOfLastAddedWork)
		work = gThreadPool.workList[gThreadPool.idxOfCurrentWork++];

	ReleaseMutex();

	return work;
}

// ------------------------------
// Thread �Լ�
// ------------------------------
DWORD WINAPI WorkerThreadFunction(LPVOID lpParam) {
	DWORD index = (DWORD)(uintptr_t)lpParam;
	HANDLE event = gThreadPool.workerEventList[index];

	while (1) {
		if (gShutdown)
			break;

		WORK work = GetWorkFromPool();

		if (work == NULL) {
			WaitForSingleObject(event, INFINITE);
			continue;
		}
		work();
	}
	_tprintf(_T("Thread %lu exiting.\n"), GetCurrentThreadId());
	return 0;
}

// ------------------------------
// ������ Ǯ ���� �� ����
// ------------------------------
DWORD MakeThreadToPool(DWORD numOfThread) {
	InitMutex();
	DWORD capacity = THREAD_MAX - gThreadPool.threadIdx;
	if (numOfThread > capacity) {
		numOfThread = capacity;
	}
	for (DWORD i = 0; i < numOfThread; i++) {
		DWORD index = gThreadPool.threadIdx;
		gThreadPool.workerEventList[index] = CreateEvent(NULL, FALSE, FALSE, NULL);

		HANDLE hThread = CreateThread( NULL, 0, WorkerThreadFunction, (LPVOID)(uintptr_t)index, 0,
		&gThreadPool.workerThreadList[index].idThread );

		gThreadPool.workerThreadList[index].hThread = hThread;
		gThreadPool.threadIdx++;
	}
	return numOfThread;
}

void ShutdownThreadPool() {
	gShutdown = TRUE;
	// ��� ������ �����
	for (DWORD i = 0; i < gThreadPool.threadIdx; i++)
		SetEvent(gThreadPool.workerEventList[i]);

	// ������ ���� ��� �� ����
	for (DWORD i = 0; i < gThreadPool.threadIdx; i++) {
		WaitForSingleObject(gThreadPool.workerThreadList[i].hThread, INFINITE);

		CloseHandle(gThreadPool.workerThreadList[i].hThread);
		CloseHandle(gThreadPool.workerEventList[i]);
	}
	DeInitMutex();
}

// ------------------------------
// �׽�Ʈ�� �۾� �Լ�
// ------------------------------
void TestFunction() {
	static int i = 0;

	AcquireMutex();

	i++;
	_tprintf(_T("No. of Test --%d : Processing thread : %lu-- \n\n"), i, GetCurrentThreadId());

	ReleaseMutex();
}
// ------------------------------
// main �Լ�
// ------------------------------
int _tmain(int argc, TCHAR* argv[]) {
	MakeThreadToPool(3);

	for (int i = 0; i < 50; i++) {
		AddWorkToPool(TestFunction);
	}

	Sleep(3000);
	ShutdownThreadPool();

	return 0;
}