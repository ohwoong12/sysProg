#include<stdio.h>
#include<tchar.h>
#include<Windows.h>
/*
#define DIR_LEN MAX_PATH+1

int _tmain(int argc, TCHAR* argv[]) {
	STARTUPINFO si = { 0, };
	PROCESS_INFORMATION pi;
	TCHAR title[] = _T("Hello Adder!!");

	si.cb = sizeof(si);
	si.lpTitle = title;
	si.dwX = 100;
	si.dwY = 200;
	si.dwXSize = 300;
	si.dwYSize = 200;
	si.dwFlags = STARTF_USEPOSITION | STARTF_USESIZE;

	TCHAR command[] = _T("ch04.exe");
	TCHAR cDir[DIR_LEN];
	BOOL state;

	GetCurrentDirectory(DIR_LEN, cDir);	//현재 디렉토리 확인
	_fputts(cDir, stdout);
	_fputts(_T("\n"),stdout);

	SetCurrentDirectory(_T("C:\\Users\\oungt\\Desktop\\coding\\SysProg\\ch04_AdderProcess\\x64\\Debug"));

	GetCurrentDirectory(DIR_LEN, cDir);
	_fputts(cDir, stdout);
	_fputts(_T("\n"), stdout);

	state = CreateProcess(NULL, command, NULL, NULL, TRUE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi);

	if (state != 0) {
		_fputts(_T("Creation OK! \n"), stdout);
	}
	else {
		_fputts(_T("Creation Error! \n"), stdout);
	}

	return 0;
}

*/

#define DIR_LEN MAX_PATH+1	//MAX_PATH는 windef.h에 선언되어 있는데 windows에서 허용하는 완전경로의 최대 길이가 얼마인지 알려줌

int _tmain(int argck, TCHAR* argv[]) {
	STARTUPINFO si = { 0, };	// STARTUPINFO 구조체 변수를 선언과 동시에 0으로 초기화, 이 변수는 CreateProcess함수의 9번째 인자로 들어가는 요소로서
	// 생성하는 프로세스의 속성을 지정하는 용도로 사용된다, 무조건 0으로 초기화 해야함.
	PROCESS_INFORMATION pi;
	TCHAR title[] = _T("AdderProcess.exe 10 20");

	si.cb = sizeof(si);	// 구조체 변수 si의 바이트 단위 크기로 멤버변수 cb를 초기화하고 있음.
	si.dwFlags = STARTF_USEPOSITION | STARTF_USESIZE;	// si 구조체 변수에 설정되어 있는 값들 중에서 반영코자 하는 멤버들에 대한 정보를 설정.
	// STARTF_USEPOSITION: 구조체 멤버 중에서 dwX와 dwY값을 참조해서, 생성하는 프로세스 윈도우 위치를 결정할 때 사용된다.
	// 또한 아무리 dwX, dwY 값을 가지고 있더라도 dwFlags에 STARTF_USEPOSITION가 설정되지 않으면 아무 의미가 없음
	si.dwX = 100;	// 프로세스 윈도우의 x 좌표
	si.dwY = 200;	// 프로세스 윈도우의 y 좌표
	si.dwXSize = 300;	// 프로세스 윈도우의 가로 길이	
	si.dwYSize = 200;	// 프로세스 윈도우의 세로 길이
	si.lpTitle = title;	// 지정한 문자열은 프로세스 윈도우의 타이틀 바 제목을 지정할 때 사용됨.

	TCHAR command[] = _T("ch04_Ex5_1_AddressProcess.exe");	// 이 프로그램을 실행
	TCHAR cDir[DIR_LEN];
	BOOL state;

	GetCurrentDirectory(DIR_LEN, cDir);	// 현재 디렉토리 확인
	_fputts(cDir, stdout);
	_fputts(_T("\n"), stdout);

	SetCurrentDirectory(_T("C:\\WinSystem"));	// 현재 디렉터리를 C:\\WinSystem 으로 변경

	GetCurrentDirectory(DIR_LEN, cDir);	//현재 디렉토리 확인
	_fputts(cDir, stdout);
	_fputts(_T("\n"), stdout);


	//첫 번째 전달인자 : NULL, 두 번째 인자를 통해서 생성하려는 프로세스 이름 정보까지 함께 전달 가능
	state = CreateProcess(NULL, command, NULL, NULL, TRUE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi);	// 이렇게 초기화 된 구조체 변수 si는 인자로 전달되고 있음.

	if (state != 0)
		_fputts(_T("Creation OK!! \n"), stdout);	// 디렉토리 확인
	else
		_fputts(_T("Creation Error!! \n"), stdout);

	return 0;
}