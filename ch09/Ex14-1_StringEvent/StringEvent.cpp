/*
StringEvent.cpp
프로그램 설명 : 1. 생산자/소비자 모델의 이해
			   2. 동기화 event에 대한 이해
*/

#include <stdio.h>
#include <tchar.h>
#include <windows.h>
#include <process.h> // _beginthreadex, _endthreadex

unsigned int WINAPI OutputThreadFunction(LPVOID lpParam);

TCHAR string[100];
HANDLE hEvent;

int _tmain(int argc, TCHAR* argv[]) {
	HANDLE hThread;
	DWORD dwThreadID;

	hEvent = CreateEvent(
		NULL,	// default 보안설명자, 상속불가
		TRUE,	// manual-reset mode로 생성
		FALSE,	// non-signaled 상태로 생성
		NULL	// 이름없는 event
	);

	if (hEvent == NULL) {
		_fputts(_T("Event object creation error \n"), stdout);
		return -1;
	}

	hThread = (HANDLE)_beginthreadex(
		NULL, 0, // 기본 보안 속성, 기본 스택 크기 설정
		OutputThreadFunction, // 쓰레드의 main 함수
		NULL, 0, // 함수에 전달할 인수는 NULL, 즉시 실행
		(unsigned*)&dwThreadID
	);

	if (hThread == 0) {
		_fputts(_T("Thread creation error \n"), stdout);
		return -1;
	}

	_fputts(_T("Insert string: "), stdout);
	_fgetts(string, 30, stdin);

	SetEvent(hEvent); // event의 state를 signaled로 변경(event실행시작신호)

	WaitForSingleObject(hThread, INFINITE);

	CloseHandle(hEvent);
	CloseHandle(hThread);
	return 0;
}
unsigned int WINAPI OutputThreadFunction(LPVOID lpParam) {
	WaitForSingleObject(hEvent, INFINITE);	// event가 signaled 상태가 되기를 기다린다.

	_fputts(_T("Output string: "), stdout);
	_fputts(string, stdout);

	return 0;
}
