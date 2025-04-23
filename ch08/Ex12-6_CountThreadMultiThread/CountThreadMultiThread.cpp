/*
CountThreadMultiThread.cpp
프로그램 설명 : _beginthreadex 함수 기반으로 변경
*/
#include <stdio.h>
#include <tchar.h>
#include <process.h> // _beginthreadex 선언
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

	// 생성 가능한 최대 개수의 쓰레드 생성
	while (TRUE) {
		hThread[cntOfThread] = (HANDLE)_beginthreadex(
			NULL,									// default 보안 속성
			1024 * 1024 * 100,						// stack size
			ThreadProc,								// thread 함수
			(LPVOID)cntOfThread,					// thread 함수의 전달인자(argument)
			0,										// default 생성 flag 지정
			(unsigned*)&dwThreadID[cntOfThread]);	// thread ID 반환

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