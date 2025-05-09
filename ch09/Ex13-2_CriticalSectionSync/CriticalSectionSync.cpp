/*
CriticalSectionSync.cpp
프로그램 설명 : 임계 영역 기반 동기화 실습
*/

#include <stdio.h>
#include <tchar.h>
#include <process.h>
#include <Windows.h>

#define NUM_OF_GATE 6

LONG gTotalCount = 0;	// 모든 쓰레드가 gTotalCount를 공유함

CRITICAL_SECTION hCriticalSection;	// 임계 영역 진입을 위한 일종의 열쇠, 소유중인 쓰레드의 ID 정보 등을 갖고 있는 구조체

/* gTotalCount 값을 읽고, 1을 더한 후 다시 메모리에 쓰는 함수 **/
void IncreaseCount() {
	EnterCriticalSection(&hCriticalSection);
	gTotalCount++; // 임계 영역 (Critical Section)
	LeaveCriticalSection(&hCriticalSection);
}

unsigned int WINAPI ThreadProc(LPVOID lpParam) {
	// 각 쓰레드를 1씩 10,000번 증가, 쓰레드가 6개이기에 60,000이 되어야 함
	for (DWORD i = 0; i < 10000; i++) {
		IncreaseCount();
	}
	return 0;
}

int _tmain(int argc, TCHAR* argv[]) {
	DWORD dwThreadId[NUM_OF_GATE];	// 6개의 쓰레드 생성
	HANDLE hThread[NUM_OF_GATE];

	InitializeCriticalSection(&hCriticalSection);	// 항상 쓰기 전에 초기화 먼저 해야함

	/** 6개의 쓰레드 생성하는 for문 */
	/** suspend 상태로 생성되어, 실행은 보류됨 */
	for (DWORD i = 0; i < NUM_OF_GATE; i++) {
		hThread[i] = (HANDLE)_beginthreadex(NULL, 0, ThreadProc, NULL, CREATE_SUSPENDED, (unsigned*)&dwThreadId[i]);

		if (hThread[i] == NULL) {
			_tprintf(_T("Thread creation fault!\n"));
			return -1;
		}
	}

	for (DWORD i = 0; i < NUM_OF_GATE; i++) {
		ResumeThread(hThread[i]);	// ResumThread() 호출 순간 쓰레드 실행, 동기화 지정 없으면 무작위 실행
	}

	WaitForMultipleObjects(NUM_OF_GATE, hThread, TRUE, INFINITE);

	_tprintf(_T("total count : %d \n"), gTotalCount);

	for (DWORD i = 0; i < NUM_OF_GATE; i++) {
		CloseHandle(hThread[i]);
	}

	DeleteCriticalSection(&hCriticalSection);	// 다 쓴 후에는 삭제를 통하여 메모리 누수 방지
	return 0;
}