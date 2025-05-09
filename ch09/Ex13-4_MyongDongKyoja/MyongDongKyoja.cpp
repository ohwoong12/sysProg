#include <stdio.h>
#include <tchar.h>
#include <time.h>
#include <windows.h>
#include <process.h>

#define NUM_OF_CUSTOMER 50			// 손님 수
#define RANGE_MIN 10				// 최소 식사 시간
#define RANGE_MAX (30 - RANGE_MIN)	// 식사 시간 범위
#define TABLE_CNT 10				// 식탁 개수 = 세마포어 초기값

CRITICAL_SECTION gElapsedTimeLock;	// 임계 영역을 위한 객체
HANDLE hSemaphore;					// 식탁 수 만큼의 동시 접근을 제한하는 세마포어 객체 (동시 접근 제한용)
DWORD randTimeArr[50];				// 손님 50명의 랜덤 식사 시간을 저장할 배열
DWORD gElapsedTime = 0;				// 전체 손님들의 식사 시간 누적합 (공유 자원이기에 Crtical Section 사용)

void TakeMeal(DWORD time) {
	DWORD thID = GetCurrentThreadId();	// 현재 쓰레드의 ID 가져오기

	WaitForSingleObject(hSemaphore, INFINITE);	// 자원이 있다면 가져오고, 없다면 무한대기

	_tprintf(_T("Enter Customer %d~ \n"), thID);
	_tprintf(_T("Customer %d having launch~\n\n"), thID);

	Sleep(100 * time); // 식사 시간 동안 대기

	EnterCriticalSection(&gElapsedTimeLock);	// 임계 영역 진입
	gElapsedTime += time;	//식사 시간 누적
	_tprintf(_T("Elapsed time for customer No. %d is %d \n"), thID, time);
	_tprintf(_T("Total serving time(minutes) is %d \n"), gElapsedTime);
	LeaveCriticalSection(&gElapsedTimeLock);	// 임계 영역 이탈

	ReleaseSemaphore(hSemaphore, 1, NULL);	// 다른 쓰레드 입장 가능하도록 세마포어 자원 반납
	_tprintf(_T("Out Customer %d \n\n"), thID);
}

unsigned int WINAPI ThreadProc(LPVOID lpParam) {
	TakeMeal((DWORD)lpParam);	// 매개변수로 받은 식사 시간 전달하여 식사 진행
	return 0;	// 쓰레드 종료
}

int _tmain(int argc, TCHAR* argv[]) {
	DWORD dwThreadId[NUM_OF_CUSTOMER];	// 쓰레드 ID 저장용 배열
	HANDLE hThread[NUM_OF_CUSTOMER];	// 쓰레드 핸들 저장용 배열

	srand((unsigned)time(NULL)); // 이어지는 rand()함수 호출에 사용될 seed 설정

	// 쓰레드에 전달할 random값 총 50개 생성
	for (int i = 0; i < NUM_OF_CUSTOMER; i++) {
			randTimeArr[i] = (DWORD)(((double)rand() / (double)RAND_MAX) *
				RANGE_MAX + RANGE_MIN);
	}	// 손님 수만큼 랜덤 식사 시간 생성 (10 ~ 30 사이)

	InitializeCriticalSection(&gElapsedTimeLock);	// 임계 영역 초기화 (필수)
	
	hSemaphore = CreateSemaphore(NULL, TABLE_CNT, TABLE_CNT, NULL);	// 세마포어 생성 (최대 TABLE_CNT명 까지 동시 접근 가능)

	if (hSemaphore == NULL)
		_tprintf(_T("Create Semaphore failed, error code is %d \n"), GetLastError());

	// Customer를 의미하는 쓰레드 생성
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

	// MAXIMUM_WAIT_OBJECTS는 64로 64명 이상의 customer에 대응 불가
	//WaitForMultipleObjects(NUM_OF_CUSTOMER, hThread, TRUE, INFINITE);
	
	// MAXIMUM_WAIT_OBJECTS는 64 해결 위해....
	for (int i = 0; i < NUM_OF_CUSTOMER; i++) {
		WaitForSingleObject(hThread[i], INFINITE);
	}

	_tprintf(_T("--- End --- \n"));

	for (int i = 0; i < NUM_OF_CUSTOMER; i++)
		CloseHandle(hThread[i]);

	CloseHandle(hSemaphore);
	return 0;
}
