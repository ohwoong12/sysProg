/*
StringEvent3.cpp
프로그램 설명 : event, mutex 동시 사용 사례
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
		NULL, // default 보안설명자, 상속불가
		TRUE, // manual-reset mode로 생성
		FALSE,// non-signaled 상태로 생성
		NULL // 이름없는 event
	);

	gSyncString.hMutex = CreateMutex(NULL, FALSE, NULL);

	if (gSyncString.hEvent == NULL || gSyncString.hMutex == NULL) {
		_fputts(_T("kernel object creation error \n"), stdout);
		return -1;
	}

	hThread[0] = (HANDLE)_beginthreadex(
		NULL, 0, // 기본 보안 속성, 기본 스택 크기 설정
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

	SetEvent(gSyncString.hEvent); // event의 state를 signaled 상태로 변경 (event 실행 시작 신호)

	WaitForMultipleObjects(
		2, // 배열의 길이, 두개 thread
		hThread, // 핸들 배열의 주소
		TRUE, // 모든 핸들이 신호받은 상태로 될 때 리턴
		INFINITE);

	CloseHandle(gSyncString.hEvent);
	CloseHandle(gSyncString.hMutex);
	CloseHandle(hThread[0]);
	CloseHandle(hThread[1]);

	return 0;
}
unsigned int WINAPI OutputThreadFunction(LPVOID lpParam) {
	// event가 signaled 상태가 되기를 기다린다.
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
	// event가 signaled 상태가 되기를 기다린다.
	WaitForSingleObject(gSyncString.hEvent, INFINITE);
	WaitForSingleObject(gSyncString.hMutex, INFINITE);

	_tprintf(_T("Output string length : %d \n"),
	_tcslen(gSyncString.string) - 1); // string에서 끝에 있는 NULL 문자는 제외

	ReleaseMutex(gSyncString.hMutex);

	return 0;
}
