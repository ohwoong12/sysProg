#include<stdio.h>
#include<tchar.h>
#include<Windows.h>

int _tmain(int argc, TCHAR* argv[])
{
	HANDLE hTimer = NULL;
	LARGE_INTEGER liDueTime;
	liDueTime.QuadPart = -50000000; // 1000������ 1�� ����(100ns)
	hTimer = CreateWaitableTimer(// Ÿ�̸� ������Ʈ ����
		NULL, // �⺻ ���� �Ӽ�, ��� �Ұ�
		TRUE, // ���� reset
		_T("Waitable Timer")
	);
	if (hTimer == NULL) {
		_tprintf(_T("CreationWaitableTimer failed (error code : %d)\n"), GetLastError());
			return -1;
	}
	_tprintf(_T("Waiting for 5 seconds...\n"));
	// Ÿ�̸��� �˶��� ��밪 5�ʷ� ����
	SetWaitableTimer(hTimer, &liDueTime, 0, NULL, NULL, FALSE);
	WaitForSingleObject(hTimer, INFINITE); // Ÿ�̸��� �˶��� ���
	_tprintf(_T("Timer was signaled.\n"));
	//MessageBeep(MB_ICONEXCLAMATION);
	MessageBeep(MB_OK);
	CloseHandle(hTimer); // Ÿ�̸� ������Ʈ�� �Ҵ�� �ڿ� ��ȯ
	return 0;
}