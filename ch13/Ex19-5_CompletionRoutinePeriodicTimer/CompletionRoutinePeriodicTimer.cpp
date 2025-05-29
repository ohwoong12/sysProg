#define _WIN32_WINNT 0x0400

#include <stdio.h>
#include <tchar.h>
#include <windows.h>

VOID CALLBACK TimerAPCProc(LPVOID, DWORD, DWORD);

int _tmain(int argc, TCHAR* argv[])
{
	HANDLE hTimer = NULL;
	LARGE_INTEGER liDueTime;
	liDueTime.QuadPart = -70000000; // 7�� (��� �ð�, 1000������ 1�� ����)

	// Ÿ�̸� ������Ʈ ����
	hTimer = CreateWaitableTimer(
		NULL, // �⺻ ���� �Ӽ�, ��� �Ұ�
		FALSE, // �ڵ� reset
		_T("Waitable Timer")	
	);

	if (hTimer == NULL) {
		_tprintf(_T("CreationWaitableTimer failed (error code : %d) \n"), GetLastError());
			return -1;
	}

	_tprintf(_T("Waiting for 7 seconds...\n")); // alarm ��ٸ��� �ð�
	
	TCHAR alstr[] = _T("Timer was signaled \n");
	LPVOID lpArg = alstr; // compile error �ؼҸ� ���� �߰��� �ڵ�

	SetWaitableTimer(hTimer,
		&liDueTime,				// Ÿ�̸��� �˶��� 7�ʷ� ����
		5000,					// �ֱ⸦ 5�ʷ� ���� (1/1000�� ����)
		TimerAPCProc,			// ������ �ݹ� ��ƾ
		lpArg,					// ��ƾ���� �ѱ� ������
		FALSE);

	// Ÿ�̸��� �˶��� ���
	int count = 0;
	
	// ��ƾ ������ ���� ���
	while (1) {
		SleepEx(INFINITE, TRUE);	// �����带 Alertable State�� ����

		// Ÿ�̸� ���� ���߱� ���� �ڵ�
		count++;	// ��ƾ�� ����� ������ SleepEx()�� �����, count�� ������
		// count�� 3 �̻��� �Ǹ�, CancelWaitableTimer()�� �ݺ� �ߴ�
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