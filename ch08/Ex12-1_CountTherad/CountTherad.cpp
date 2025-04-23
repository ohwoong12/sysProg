/*
CountThread.cpp
프로그램 설명 : 생성 가능한 쓰레드의 개수 측정
*/
#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

#define MAX_THREADS (1024*10)

DWORD WINAPI ThreadProc(LPVOID lpParam) {
	DWORD threadNum = (DWORD)lpParam;
	while (TRUE) {
		_tprintf(_T("thread num : %d \n"), threadNum);
		Sleep(5000);
	}
	return 0;
}

DWORD cntOfThread = 0;
int _tmain(int argc, TCHAR* argv[]) {
	DWORD dwThreadID[MAX_THREADS];
	HANDLE hThread[MAX_THREADS];

	// 생성 가능한 최대 개수의 쓰레드 생성
	while (TRUE) {
		hThread[cntOfThread] = CreateThread(
			NULL,						// default 보안 속성
			1024 * 1024 * 100,			// stack size (100MB)
			ThreadProc,					// thread 함수
			(LPVOID)cntOfThread,		// thread 함수의 전달인자(argument)
			0,							// thread 생성 즉시 실행되도록 설정
			&dwThreadID[cntOfThread]);	// thread ID 반환

		// 쓰레드 생성 확인
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