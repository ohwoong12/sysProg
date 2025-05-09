#include<stdio.h>
#include<tchar.h>
#include<Windows.h>
#include<process.h>

LONG gTotalCount = 0;
HANDLE hMutex;

unsigned int WINAPI IncreaseCountOne(LPVOID lpParam) {
	WaitForSingleObject(hMutex, INFINITE);
	gTotalCount++;
	return 0;
}

unsigned int WINAPI IncreaseCountTwo(LPVOID lpParam) {
	DWORD dwWaitResult = 0;
	dwWaitResult = WaitForSingleObject(hMutex, INFINITE);

	switch (dwWaitResult) {
	case WAIT_OBJECT_0:
		_tprintf(_T("Mutex has released successfully in the previous thread. \n"));
			ReleaseMutex(hMutex);
		return -1;
	case WAIT_ABANDONED:
		_tprintf(_T("WAIT_ABANDONED \n"));
		break;
	}

	gTotalCount++;
	ReleaseMutex(hMutex);
	return 0;
}int _tmain(int argc, TCHAR* argv[]) {
	DWORD dwThreadIdOne;
	DWORD dwThreadIdTwo;
	HANDLE hThreadOne;
	HANDLE hThreadTwo;

	hMutex = CreateMutex(NULL, FALSE, NULL);

	if (hMutex == NULL) {
		_tprintf(_T("CreateMutex error : %d\n"), GetLastError());
		return -1;
	}

	hThreadOne = (HANDLE)_beginthreadex(NULL, 0, IncreaseCountOne, NULL, 0, (unsigned*)&dwThreadIdOne);
	hThreadTwo = (HANDLE)_beginthreadex(NULL, 0, IncreaseCountTwo, NULL, CREATE_SUSPENDED, (unsigned*)&dwThreadIdTwo);

	Sleep(1000);
	ResumeThread(hThreadTwo);

	WaitForSingleObject(hThreadOne, INFINITE);
	WaitForSingleObject(hThreadTwo, INFINITE);

	_tprintf(_T("total count: %d \n"), gTotalCount);

	CloseHandle(hThreadOne);
	CloseHandle(hThreadTwo);
	CloseHandle(hMutex);
	return 0;
}