#include<stdio.h>
#include<tchar.h>
#include<windows.h>

int _tmain(int argc, TCHAR* argv[])
{
	HANDLE hTimer = NULL;
	LARGE_INTEGER liDueTime;
	liDueTime.QuadPart = -50000000; // 1000������ 1�� ����(100ns)
	hTimer = CreateWaitableTimer(// Ÿ�̸� ������Ʈ ����
		NULL, // �⺻ ���� �Ӽ�, ��� �Ұ�
		FALSE, // �ڵ� reset
		_T("Waitable Timer"));
	if (hTimer == NULL) {
		_tprintf(_T("CreationWaitableTimer failed (error code : %d)\n"), GetLastError());
			return -1;
	}
	_tprintf(_T("Waiting for 5 seconds...\n"));
	// �˶��� 5�� ��, �ֱ⸦ 2�ʷ� ����
	SetWaitableTimer(hTimer, &liDueTime, 2000, NULL, NULL, FALSE);
	int count = 0;
	while (1) {// Ÿ�̸��� �˶��� ��� WaitForSingleObject(hTimer, INFINITE);
		_tprintf(_T("Timer was signaled.\n"));
		MessageBeep(MB_OK);
		count++; if (count >= 3) {
			CancelWaitableTimer(hTimer); // �������� Ÿ�̸� ����
			break;
		}
	}
	CloseHandle(hTimer); // Ÿ�̸� ������Ʈ�� �Ҵ�� �ڿ� ��ȯ
	return 0;
}