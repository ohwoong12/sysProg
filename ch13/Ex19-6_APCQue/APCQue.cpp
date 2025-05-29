#define _WIN32_WINNT 0X0400

#include <stdio.h>
#include <tchar.h>
#include <windows.h>

VOID CALLBACK APCProc(ULONG_PTR);

int _tmain(int argc, TCHAR* argv[])
{
	// 현재 쓰레드의 핸들 갖고오기 -> APC 루틴을 등록할 대상
	HANDLE hThread = GetCurrentThread();
	
	// APCProc() 함수를 현재 쓰레드의 APC Queue에 등록
	// 인자로는 1~7까지의 값을 각각 전달
	QueueUserAPC(APCProc, hThread, (ULONG_PTR)1);
	QueueUserAPC(APCProc, hThread, (ULONG_PTR)2);
	QueueUserAPC(APCProc, hThread, (ULONG_PTR)3);
	QueueUserAPC(APCProc, hThread, (ULONG_PTR)4);
	QueueUserAPC(APCProc, hThread, (ULONG_PTR)5);
	QueueUserAPC(APCProc, hThread, (ULONG_PTR)6);
	QueueUserAPC(APCProc, hThread, (ULONG_PTR)7);

	Sleep(500);

	// 이 함수로 현재 쓰레드를 Alertable State로 만들고 대기
	// APC 루틴이 모두 실행되면 SleepEx()는 반환됨
	SleepEx(INFINITE, TRUE);

	return 1;
}

// 실행될 APC 루틴(완료 루틴)
// dwParam은 사용자 정의 인자, 여기에서는 숫자 1~7
VOID CALLBACK APCProc(ULONG_PTR dwParam)
{
	_tprintf(_T("Asynchronous procedure call num : %u \n"),
		(DWORD)dwParam);
}