#include<stdio.h>
#include<tchar.h>
#include<Windows.h>

int _tmain(int argc, TCHAR* argv[])
{
	HANDLE hTimer = NULL;
	LARGE_INTEGER liDueTime;
	liDueTime.QuadPart = -50000000; // 1000만분의 1초 단위(100ns)
	hTimer = CreateWaitableTimer(// 타이머 오브젝트 생성
		NULL, // 기본 보안 속성, 상속 불가
		TRUE, // 수동 reset
		_T("Waitable Timer")
	);
	if (hTimer == NULL) {
		_tprintf(_T("CreationWaitableTimer failed (error code : %d)\n"), GetLastError());
			return -1;
	}
	_tprintf(_T("Waiting for 5 seconds...\n"));
	// 타이머의 알람을 상대값 5초로 설정
	SetWaitableTimer(hTimer, &liDueTime, 0, NULL, NULL, FALSE);
	WaitForSingleObject(hTimer, INFINITE); // 타이머의 알람을 대기
	_tprintf(_T("Timer was signaled.\n"));
	//MessageBeep(MB_ICONEXCLAMATION);
	MessageBeep(MB_OK);
	CloseHandle(hTimer); // 타이머 오브젝트에 할당된 자원 반환
	return 0;
}