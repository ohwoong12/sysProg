#define _WIN32_WINNT 0x0400

#include <stdio.h>
#include <tchar.h>
#include <windows.h>

VOID CALLBACK TimerAPCProc(LPVOID, DWORD, DWORD);

int _tmain(int argc, TCHAR* argv[])
{
	HANDLE hTimer = NULL;
	LARGE_INTEGER liDueTime;
	liDueTime.QuadPart = -70000000; // 7초 (상대 시간, 1000만분의 1초 단위)

	// 타이머 오브젝트 생성
	hTimer = CreateWaitableTimer(
		NULL, // 기본 보안 속성, 상속 불가
		FALSE, // 자동 reset
		_T("Waitable Timer")	
	);
	if (hTimer == NULL) {
		_tprintf(_T("CreationWaitableTimer failed (error code : %d) \n"), GetLastError());
			return -1;
	}
	_tprintf(_T("Waiting for 7 seconds...\n")); // alarm 기다리는 시간
	TCHAR alstr[] = _T("Timer was signaled \n");
	LPVOID lpArg = alstr; // compile error 해소를 위해 추가된 코드
	SetWaitableTimer(hTimer,
		&liDueTime, // 타이머의 알람을 7초로 설정
		5000, // 주기를 5초로 설정 (1/1000초 단위)
		TimerAPCProc, lpArg, FALSE);

	// 타이머의 알람을 대기
	int count = 0;
	
	while (1) {
		SleepEx(INFINITE, TRUE);
		// timer 동작 멈추기 위한 코드
		count++;
		if (count >= 3) {
			CancelWaitableTimer(hTimer);
			break;
		}
	}
	CloseHandle(hTimer);
	return 0;
}

VOID CALLBACK TimerAPCProc(LPVOID lpArg, DWORD timerLowVal, DWORD timerHighVal)
{
	_tprintf(_T("%s"), (TCHAR*)lpArg);
	MessageBeep(MB_ICONEXCLAMATION);
}