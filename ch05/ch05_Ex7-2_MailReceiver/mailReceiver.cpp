#include<stdio.h>
#include<tchar.h>
#include<Windows.h>

#define SLOT_NAME _T("\\\\.\\mailslot\\mailbox")

int _tmain(int argc, TCHAR* argv[]) {
	HANDLE hMailSlot;	//masilslot �ڵ�
	TCHAR messageBox[50];
	DWORD bytesRead;	//number of bytes read

	/*mailslot ����*/
	/*
	SLOT_NAME�� ������� ���Ͻ����� ����, �� �ּҰ� ���Ͻ����� �ּҷ� ����
	�� Receiver�� �����͸� �������� �Ѵٸ� ���ǵǾ� �ִ� �ּҷθ� ������ ��
	*/
	hMailSlot = CreateMailslot(SLOT_NAME, 0, MAILSLOT_WAIT_FOREVER, NULL);	
	if (hMailSlot == INVALID_HANDLE_VALUE) {
		_fputts(_T("Unable to create mailslot! \n"), stdout);	//_fputts�� Ư�� ��Ʈ��(��:����)�� ���ڿ��� ����ϴ� �Լ�
		return -1;
	}

	/*Message ����*/
	_fputts(_T("******* Message *******"), stdout);
	while (1) {
		//ReadFile�Լ��� ���ؼ� ���Ͻ������� ���޵� �����͸� �а� ����
		if (!ReadFile(hMailSlot, messageBox, sizeof(TCHAR) * 50, &bytesRead, NULL)) {
			_fputts(_T("Unable to read!"), stdout);
			CloseHandle(hMailSlot);
			return 1;
		}

		if (!_tcsncmp(messageBox, _T("exit"), 4)) {
			_fputts(_T("Good Bye!"), stdout);
			break;
		}

		messageBox[bytesRead / sizeof(TCHAR)] = 0;	//NULL ���� ����
		_fputts(messageBox, stdout);
	}

	CloseHandle(hMailSlot);
	return 0;
}