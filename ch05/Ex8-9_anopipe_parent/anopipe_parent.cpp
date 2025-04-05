/* anonymous pipe를 통해 동일 프로세스 내 통신이 아닌,
서로 다른 두 프로세스간(부모-자식) 통신 구현하기
anopipe_parent.cpp
프로그램 설명: 이름없는 파이프 부모 프로세스(파이프 생성, 파이프에 메세지 쓰기)
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <tchar.h>
#include <windows.h>
int _tmain(int argc, LPTSTR argv[])
{
	HANDLE hReadPipe, hWritePipe; //pipe handle
	TCHAR sendString[] = _T("anonymous pipe 2");
	DWORD bytesWritten;
	SECURITY_ATTRIBUTES sa;
	sa.nLength = sizeof(sa);
	sa.lpSecurityDescriptor = NULL;	// Pipe 생성(CreatePipe)시 핸들 상속 가능(bInheritHandles = TRUE)으로 설정
	sa.bInheritHandle = TRUE; 
	/*
	anopipe_child.exe는 anopipe_parent 프로세스에서 CreatProcess() 함수로 생성하여 사용 할 것.
	이때 child procces인 anopipe_child는 hReadPipe의 핸들 정보(핸들 번호와 그에 해당하는 주소)를 알고 있어야 올바르게 실행 됨.
	즉, 핸들 정보를 상속받아야 올바른 주소에서 메시지를 읽어 올 수 있음.
	이것이 Pipe를 상속 가능한 핸들로 설정하는 이유
	*/
	//pipe 생성
	CreatePipe(&hReadPipe, &hWritePipe, &sa, 0); // Pipe를 상속 가능(Y) 핸들로 설정
	//pipe의 한쪽 끝을 이용한 데이터 송신
	WriteFile(hWritePipe, sendString, _tcslen(sendString) * sizeof(TCHAR), &bytesWritten, NULL);
	_tprintf(_T("string send: %s, written in bytes : %d \n"), sendString, bytesWritten);
	TCHAR command[1024];
	//command line으로 handle 정보 전달하기
	_stprintf(command, _T("%s %u %u"), _T("Ex8-9_anopipe_child.exe"), (unsigned)hReadPipe, bytesWritten);
	_tprintf(_T("hReadPipe: %d \n"), (unsigned)hReadPipe);


	STARTUPINFO si = { 0, };
	PROCESS_INFORMATION pi;
	si.cb = sizeof(si);
	BOOL state;
	state = CreateProcess(NULL, command, NULL, NULL, TRUE, CREATE_NEW_CONSOLE | NORMAL_PRIORITY_CLASS, NULL, NULL, &si, &pi);
	if (state == 0) {
		_fputts(_T("file creation failed\n"), stdout);
	}
	else {
		_fputts(_T("file creation success\n"), stdout);
	}

	CloseHandle(hReadPipe);
	CloseHandle(hWritePipe);
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
	
	return 0;
}