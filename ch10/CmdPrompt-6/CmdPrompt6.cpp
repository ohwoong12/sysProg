/*
CmdPrompt6.cpp (CmdPrompt6.exe)
프로그램 설명 : 명령 프롬프트 프로젝트 6
*/
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <tchar.h>
#include <windows.h>
#include <locale.h>
#include <tlhelp32.h>

#define STR_LEN 256
#define CMD_TOKEN_NUM 10

int CmdTokenize(void);
int CmdProcessing(int);		// exit, echo hello world
int ListProcessInfo(void);	// lp
void KillProcess(void);		// kp
void start_op(int);			// start, start echo test
void sort_op(void);			// sort, sort > xxx.txt
void TypeTextFile(void);

TCHAR cmdString[STR_LEN];
TCHAR cmdTokenList[CMD_TOKEN_NUM][STR_LEN];
TCHAR seps[] = _T(" ,\t\n");

int _tmain(int argc, TCHAR* argv[]) {
	// 한글 입력을 가능케 하기 위해
	_tsetlocale(LC_ALL, _T("Korean"));

	DWORD isExit = NULL;

	// 프로그램 main()에 전달인자가 있는 경우 고려
	if (argc >= 2) {
		for (int i = 1; i < argc; i++) {
			_tcscpy(cmdTokenList[i - 1], argv[i]); //tokenize() 기능
		}
		// argc-1 => tokenNum, cmdprompt.exe 다음 string이 첫번째 token
		isExit = CmdProcessing(argc - 1);
		if (isExit == TRUE) {
			_fputts(_T("명령어 처리를 종료합니다. \n"), stdout);
			return 0;
		}
	}

	while (1) {
		int tokenNum = CmdTokenize();
		if (tokenNum == 0) // Enter 입력시 처리
			continue;
		isExit = CmdProcessing(tokenNum);
		if (isExit == TRUE) {
			_fputts(_T("명령어 처리를 종료합니다. \n"), stdout);
			break;
		}
	}
	return 0;
}

// command prompt에 입력되는 string들을 token(개별 문자열)으로 분리하는 작업
int CmdTokenize() {
	TCHAR* token;

	_fputts(_T("USW command >> "), stdout);
	_fgetts(cmdString, 256, stdin);

	token = _tcstok(cmdString, seps);

	int tokenNum = 0;

	while (token != NULL) {
		// 각각의 문자열(token)들을 cmd list 배열에 저장
		// 대문자를 소문자로 바꾸는 기본 함수인 _tcslwr() 사용
		_tcscpy(cmdTokenList[tokenNum++], _tcslwr(token));
		// cmdString에서 NULL로 구분된 다음 문자열 불러오기
		token = _tcstok(NULL, seps);
	}
	return tokenNum;
}

int CmdProcessing(int tokenNum)
{
	TCHAR ERROR_CMD[] = _T("'%s'은(는) 실행할 수 있는 프로그램이 아닙니다. \n");
	BOOL isRun;
	STARTUPINFO si = { 0, };
	PROCESS_INFORMATION pi;
	si.cb = sizeof(si);
	TCHAR cmdStringWithOptions[STR_LEN] = { 0, };
	TCHAR optString[STR_LEN] = { 0, };

	if (!_tcscmp(cmdTokenList[0], _T("exit"))) {
		return TRUE;
	}
	else if (!_tcscmp(cmdTokenList[0], _T("start"))) {
		start_op(tokenNum);
	}
	else if (!_tcscmp(cmdTokenList[0], _T("echo"))) {
		// 입력된 문자열을 하나의 string으로 구성, 그대로 출력
		for (int i = 1; i < tokenNum; i++)
			_stprintf(optString, _T("%s %s"), optString, cmdTokenList[i]);
		_tprintf(_T("echo message : %s \n"), optString);
	}
	else if (!_tcscmp(cmdTokenList[0], _T("lp"))) {
		// list all processes currently running on the system
		int retval = ListProcessInfo();
		if (retval < 0)
			_tprintf(_T("ListProcessInfo() call error! \n"));
	}
	else if (!_tcscmp(cmdTokenList[0], _T("kp"))) {
		if (tokenNum > 1) {
			KillProcess();
		}
		else {
			// kp 만 입력된 경우
			_tprintf(_T("usage : kp <process Name> \n"));
		}
	}
	else if (!_tcscmp(cmdTokenList[0], _T("sort"))) {
		sort_op();
	}
	else if (!_tcscmp(cmdTokenList[0], _T("uswtype"))) {
		TypeTextFile();
}
else {
	_tcscpy(cmdStringWithOptions, cmdTokenList[0]);
	for (int i = 1; i < tokenNum; i++) {
		_stprintf(cmdStringWithOptions, _T("%s %s"), cmdStringWithOptions, cmdTokenList[i]);
	}
	isRun = CreateProcess(NULL, cmdStringWithOptions, NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi);
	if (isRun == FALSE)
		_tprintf(ERROR_CMD, cmdTokenList[0]);

	// Wait until child process exits.
	WaitForSingleObject(pi.hProcess, INFINITE);
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
	}
	for (int i = 0; i < tokenNum; i++) {
		*cmdTokenList[i] = { 0, };
	}
	return 0;
}

void start_op(int tokenNum)
{
	BOOL isRun;
	STARTUPINFO si = { 0, };
	PROCESS_INFORMATION pi;
	si.cb = sizeof(si);
	TCHAR cmdStringWithOptions[STR_LEN] = { 0, };
	TCHAR optString[STR_LEN] = { 0, };

	// start 외 추가 문자열 처리 (예: start echo Hello U of SW)
	if (tokenNum > 1) {
		for (int i = 1; i < tokenNum; i++)
			_stprintf(optString, _T("%s %s"), optString, cmdTokenList[i]);
		_stprintf(cmdStringWithOptions, _T("%s %s"), _T("CmdPrompt6.exe"), optString);
	}
	else
		// start 만 입력된 경우
		_stprintf(cmdStringWithOptions, _T("%s"), _T("CmdPrompt6.exe"));
	isRun = CreateProcess(NULL, cmdStringWithOptions, NULL, NULL, TRUE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi);
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
}

int ListProcessInfo()
{
	HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,
		0);
	if (hProcessSnap == INVALID_HANDLE_VALUE) {
		_tprintf(_T("CreateToolhelp32Snapshot error! \n"));
		return -1;
	}
	// 프로세스 정보 얻기 위한 구조체 변수
	PROCESSENTRY32 pe32;
	pe32.dwSize = sizeof(PROCESSENTRY32);
	if (!Process32First(hProcessSnap, &pe32)) {
		_tprintf(_T("Process32First error! \n"));
		CloseHandle(hProcessSnap);
		return -1;
	}
	do {
		_tprintf(_T("%25s %5d \n"), pe32.szExeFile,
			pe32.th32ProcessID);
	} while (Process32Next(hProcessSnap, &pe32));
	CloseHandle(hProcessSnap);
	return 0;
}

void KillProcess(void)
{
	HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,
		0);
	if (hProcessSnap == INVALID_HANDLE_VALUE) {
		_tprintf(_T("CreatToolhelp32Snapshot error!\n"));
		return;
	}
	PROCESSENTRY32 pe32;
	pe32.dwSize = sizeof(PROCESSENTRY32);
	if (!Process32First(hProcessSnap, &pe32)) {
		_tprintf(_T("Process32First error! \n"));
		CloseHandle(hProcessSnap);
		return;
	}
	HANDLE hProcess;
	BOOL isKill = FALSE;
	TCHAR* fileName;

	do {
		// szExeFile을 소문자로 전환 (cmdToeknList[1]에는 소문자로 넘어와....)
		fileName = _tcslwr(pe32.szExeFile);

		// 입력된 프로세스 이름과 비교하여 같은 이름을 종료시킨다
		//if (_tcscmp(pe32.szExeFile, cmdTokenList[1]) == 0) {
		if (_tcscmp(fileName, cmdTokenList[1]) == 0) {
			// 프로세스 이름에 해당하는 프로세스 ID의 핸들을 받는다
			hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pe32.th32ProcessID);
			if (hProcess != NULL) {
				// 프로세스 강제 종료
				TerminateProcess(hProcess, -1);
				isKill = TRUE;
			}
			CloseHandle(hProcess);
			break;
		}
	} while (Process32Next(hProcessSnap, &pe32));
	CloseHandle(hProcessSnap);
	if (isKill == FALSE)
		_tprintf(_T("Kill process failed, Try again! \n"));
}

void sort_op(void)
{
	BOOL isRun;
	STARTUPINFO si = { 0, };
	PROCESS_INFORMATION pi;
	si.cb = sizeof(si);
	if (!_tcscmp(cmdTokenList[1], _T(">"))) { // 같을 때 리턴 값 0

		// "sort > sort.txt"와 같이 명령어가 입력되면 아래 코드 실행
		SECURITY_ATTRIBUTES sa = { sizeof(SECURITY_ATTRIBUTES), NULL, TRUE };
		HANDLE hFile = CreateFile(cmdTokenList[2], GENERIC_WRITE, FILE_SHARE_READ, &sa, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		si.hStdOutput = hFile;
		si.hStdInput = GetStdHandle(STD_INPUT_HANDLE);
		si.hStdError = GetStdHandle(STD_ERROR_HANDLE);
		si.dwFlags |= STARTF_USESTDHANDLES;

		// cmdTokenList[0] -> sort
		isRun = CreateProcess(NULL, cmdTokenList[0], NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi);
		WaitForSingleObject(pi.hProcess, INFINITE);
		CloseHandle(hFile);
	}
	else {
		isRun = CreateProcess(NULL, cmdTokenList[0], NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
		WaitForSingleObject(pi.hProcess, INFINITE);
	}
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
}

void TypeTextFile(void)
{
	TCHAR cmdStringWithOptions[STR_LEN] = { 0, };
	BOOL isRun;

	if (!_tcscmp(cmdTokenList[2], _T("|")) && !_tcscmp(cmdTokenList[4], _T(">"))) {
		HANDLE hReadPipe, hWritePipe;
		SECURITY_ATTRIBUTES pipeSA = { sizeof(SECURITY_ATTRIBUTES), NULL, TRUE };
		CreatePipe(&hReadPipe, &hWritePipe, &pipeSA, 0);

		// uswtype 프로세스
		STARTUPINFO siType = { 0, };
		PROCESS_INFORMATION piType;

		siType.cb = sizeof(siType);
		siType.hStdInput = GetStdHandle(STD_INPUT_HANDLE);
		siType.hStdOutput = hWritePipe;
		siType.hStdError = GetStdHandle(STD_ERROR_HANDLE);
		siType.dwFlags |= STARTF_USESTDHANDLES;

		_stprintf(cmdStringWithOptions, _T("%s %s"), cmdTokenList[0], cmdTokenList[1]);
		CreateProcess(NULL, cmdStringWithOptions, NULL, NULL, TRUE, 0, NULL, NULL, &siType, &piType);

		CloseHandle(piType.hThread);
		CloseHandle(hWritePipe); // 중요

		// sort 프로세스
		SECURITY_ATTRIBUTES fileSA = { sizeof(SECURITY_ATTRIBUTES), NULL, TRUE };
		HANDLE hFile = CreateFile(cmdTokenList[5], GENERIC_WRITE, FILE_SHARE_READ, &fileSA, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

		STARTUPINFO siSort = { 0, };
		PROCESS_INFORMATION piSort;

		siSort.cb = sizeof(siSort);
		siSort.hStdInput = hReadPipe;
		siSort.hStdOutput = hFile;
		siSort.hStdError = GetStdHandle(STD_ERROR_HANDLE);
		siSort.dwFlags |= STARTF_USESTDHANDLES;

		CreateProcess(NULL, cmdTokenList[3], NULL, NULL, TRUE, 0, NULL, NULL, &siSort, &piSort);

		CloseHandle(piSort.hThread);
		CloseHandle(hReadPipe);
		CloseHandle(hFile);

		WaitForSingleObject(piType.hProcess, INFINITE);
		WaitForSingleObject(piSort.hProcess, INFINITE);

		CloseHandle(piType.hProcess);
		CloseHandle(piSort.hProcess);
	}

	else if (!_tcscmp(cmdTokenList[2], _T("|"))) {
		HANDLE hReadPipe, hWritePipe;
		SECURITY_ATTRIBUTES pipeSA = { sizeof(SECURITY_ATTRIBUTES), NULL, TRUE };

		CreatePipe(&hReadPipe, &hWritePipe, &pipeSA, 0);

		STARTUPINFO siType = { 0, };
		PROCESS_INFORMATION piType;

		siType.cb = sizeof(siType);
		siType.hStdInput = GetStdHandle(STD_INPUT_HANDLE);
		siType.hStdOutput = hWritePipe;
		siType.hStdError = GetStdHandle(STD_ERROR_HANDLE);
		siType.dwFlags |= STARTF_USESTDHANDLES;

		_stprintf(cmdStringWithOptions, _T("%s %s"), cmdTokenList[0], cmdTokenList[1]);
		CreateProcess(NULL, cmdStringWithOptions, NULL, NULL, TRUE, 0, NULL, NULL, &siType, &piType);
		CloseHandle(piType.hThread);
		CloseHandle(hWritePipe);

		STARTUPINFO siSort = { 0, };
		PROCESS_INFORMATION piSort;
		siSort.cb = sizeof(siSort);
		siSort.hStdInput = hReadPipe;
		siSort.hStdOutput = GetStdHandle(STD_OUTPUT_HANDLE);
		siSort.hStdError = GetStdHandle(STD_ERROR_HANDLE);
		siSort.dwFlags |= STARTF_USESTDHANDLES;

		CreateProcess(NULL, cmdTokenList[3], NULL, NULL, TRUE, 0, NULL, NULL, &siSort, &piSort);
		CloseHandle(piSort.hThread);
		CloseHandle(hReadPipe);

		WaitForSingleObject(piType.hProcess, INFINITE);
		WaitForSingleObject(piSort.hProcess, INFINITE);
		CloseHandle(piType.hProcess);
		CloseHandle(piSort.hProcess);
	}

	// case 3: uswtype 단독 실행
	else {
		_stprintf(cmdStringWithOptions, _T("%s %s"), cmdTokenList[0], cmdTokenList[1]);
		STARTUPINFO si = { 0, };
		PROCESS_INFORMATION pi;
		si.cb = sizeof(si);
		CreateProcess(NULL, cmdStringWithOptions, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
		WaitForSingleObject(pi.hProcess, INFINITE);
		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);
	}
}
