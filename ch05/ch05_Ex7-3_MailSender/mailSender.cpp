/*
	Receiver를 먼저 띄운 다음에 Sender를 띄워야 함
	이유: Sender에서는 CreateFile 함수를 호출하면서 5번째 인자로 OPEN_EXISTING을 전달하고 있기 때문임
*/
#include<stdio.h>
#include<tchar.h>
#include<Windows.h>

#define SLOT_NAME _T("\\\\.\\mailslot\\mailbox")

int _tmain(int argc, TCHAR* argv[]) {
	HANDLE hMailSlot;
	TCHAR Message[50];
	DWORD bytesWritten;

	//CreateFile 함수를 호출하면서 메일슬롯에 메시지를 전달하기 위한 데이터 스트림을 생성
	hMailSlot = CreateFile(SLOT_NAME, GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hMailSlot == INVALID_HANDLE_VALUE) {
		_fputts(_T("Unable to create mailslot! \n"), stdout);
		return 1;
	}

	while (1) {
		_fputts(_T("MY Message>"), stdout);
		_fgetts(Message, sizeof(Message) / sizeof(TCHAR), stdin);

		if (!WriteFile(hMailSlot, Message, _tcslen(Message) * sizeof(TCHAR), &bytesWritten, NULL)) {
			_fputts(_T("unable to write!"), stdout);
			CloseHandle(hMailSlot);
			return 1;
		}

		if (!_tcscmp(Message, _T("exit"))) {
			_fputts(_T("Good Bye!"), stdout);
			break;
		}
	}
	CloseHandle(hMailSlot);
	return 0;
}