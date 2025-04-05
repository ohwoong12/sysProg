#include<stdio.h>
#include<tchar.h>
#include<Windows.h>

#define SLOT_NAME _T("\\\\.\\mailslot\\mailbox")

int _tmain(int argc, TCHAR* argv[]) {
	HANDLE hMailSlot;	//masilslot 핸들
	TCHAR messageBox[50];
	DWORD bytesRead;	//number of bytes read

	/*mailslot 생성*/
	/*
	SLOT_NAME을 기반으로 메일슬롯을 생성, 이 주소가 메일슬롯의 주소로 결정
	이 Receiver로 데이터를 보내고자 한다면 정의되어 있는 주소로만 보내야 함
	*/
	hMailSlot = CreateMailslot(SLOT_NAME, 0, MAILSLOT_WAIT_FOREVER, NULL);	
	if (hMailSlot == INVALID_HANDLE_VALUE) {
		_fputts(_T("Unable to create mailslot! \n"), stdout);	//_fputts는 특정 스트림(예:파일)에 문자열을 출력하는 함수
		return -1;
	}

	/*Message 수신*/
	_fputts(_T("******* Message *******"), stdout);
	while (1) {
		//ReadFile함수를 통해서 메일슬롯으로 전달된 데이터를 읽고 있음
		if (!ReadFile(hMailSlot, messageBox, sizeof(TCHAR) * 50, &bytesRead, NULL)) {
			_fputts(_T("Unable to read!"), stdout);
			CloseHandle(hMailSlot);
			return 1;
		}

		if (!_tcsncmp(messageBox, _T("exit"), 4)) {
			_fputts(_T("Good Bye!"), stdout);
			break;
		}

		messageBox[bytesRead / sizeof(TCHAR)] = 0;	//NULL 문자 삽입
		_fputts(messageBox, stdout);
	}

	CloseHandle(hMailSlot);
	return 0;
}