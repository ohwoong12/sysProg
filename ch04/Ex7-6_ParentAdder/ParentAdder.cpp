/*
ParentAdder.cpp
프로그램 설명
1. 1~10까지 덧셈하여 출력
*/

#include<stdio.h>
#include<tchar.h>
#include<Windows.h>

int _tmain(int argc, TCHAR* argv[]) {
	STARTUPINFO si1 = { 0, };
	STARTUPINFO si2 = { 0, };

	PROCESS_INFORMATION pi1;
	PROCESS_INFORMATION pi2;

	DWORD return_val1;
	DWORD return_val2;

	TCHAR command1[] = _T("Ex7-4_PartAdder 1 5");	// PartAdder.exe의 실행을 위한 문자열 배열 선언
	TCHAR command2[] = _T("Ex7-4_PartAdder 6 10");

	DWORD sum = 0;

	si1.cb = sizeof(si1);
	si2.cb = sizeof(si2);

	CreateProcess(NULL, command1, NULL, NULL, TRUE, 0, NULL, NULL, &si1, &pi1);	// 프로세스 생성, _tmain 함수에 인자 전달
	CreateProcess(NULL, command2, NULL, NULL, TRUE, 0, NULL, NULL, &si2, &pi2);

	CloseHandle(pi1.hThread);	// 쓰레드는 나중에
	CloseHandle(pi2.hThread);

	/*문제 해결을 위해 추가되는 두 줄의 코드*/
	WaitForSingleObject(pi1.hProcess, INFINITE);	// 자식 프로세스가 종료될 때까지 기다려 주는 코드
	WaitForSingleObject(pi2.hProcess, INFINITE);

	GetExitCodeProcess(pi1.hProcess, &return_val1);	// 자식 프로세스들이 종료하면서 전달하는 종료코드를 얻기 위해 함수 사용
	GetExitCodeProcess(pi2.hProcess, &return_val2);

	if (return_val1 == -1 || return_val2 == -1)	// 자식 프로세스가 비정상 종료를 했는지 확인
		return -1;	//-1값 반환되면 비정상적 종료

	sum += return_val1;	// sum 변수에 val1과 val2 더함
	sum += return_val2;

	_tprintf(_T("total : %d \n"), sum);	// 출력

	CloseHandle(pi1.hProcess);	// 다 썼으니 핸들 닫음으로써 자식프로세스 커널 오브젝트 완전 소멸
	CloseHandle(pi2.hProcess);

	return 0;
}