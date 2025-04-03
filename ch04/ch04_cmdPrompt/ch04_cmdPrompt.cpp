//프로그램 설명: exit 명령어 + echo 명령어/tokenize()함수 + CreateProcess() 추가
#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<tchar.h>
#include<locale.h>
#include<windows.h>

#define STR_LEN 256
#define CMD_TOKEN_NUM 10

TCHAR cmdString[STR_LEN];
TCHAR cmdTokenList[CMD_TOKEN_NUM][STR_LEN];
TCHAR seps[] = _T(" , \t\n");
//TCHAR promptMessage[STR_LEN] = _T("USW command >>");


int CmdProcessing(int);	/*	함수: int CmdProcessing(void)
								기능: 명령어를 입력 받아서 해당 명령어에 지정되어 있는 기능을 수행한다.
								exit가 입력되면 TRUE를 반환하고 이는 프로그램 종료로 이어진다.	*/
int CmdTokenize(void);


int _tmain(int argc, TCHAR* argv[]) {
	_tsetlocale(LC_ALL, _T("korean"));	//한글 처리를 가능하게 함

	DWORD isExit = NULL;
	//int tokenNum = 0;	//프로그램 main()에 전달인자가 있는 경우 고려

	if (argc >= 2) {
		for (int i = 1; i < argc; i++) {
			//cmdprompt.exe. 다음 string이 첫번째 토큰
			_tcscpy(cmdTokenList[i - 1], argv[i]);	//tokenize() 기능
		}
		//tokenNum = argc - 1;
		isExit = CmdProcessing(argc - 1);
		if (isExit == TRUE) {
			_fputts(_T("-----명령어 처리를 종료합니다----- \n"), stdout);
			return 0;
		}
	}

	while (1) {
		int tokenNum = CmdTokenize();

		if (tokenNum == 0) 	//Enter 입력 시 처리
			continue;

		isExit = CmdProcessing(argc - 1);

		if (isExit == TRUE) {
			_fputts(_T("-----명령어 처리를 종료합니다.----- \n"), stdout);
			break;
		}
	}

	return 0;
}

//cmd를 통해 입려되는 string을 token(개별 문자열)으로 분리하는 작업
int CmdTokenize() {
	TCHAR* token;

	_fputts(_T("USW command >> "), stdout);
	_fgetts(cmdString, 256, stdin);

	token = _tcstok(cmdString, seps);

	int tokenNum = 0;

	while (token != NULL) {
		// 각각의 문자열(token)들을 cmd list 배열에 저장
		// 대문자를 소문자로 바꾸는 기능은 StrLower()에서 기본 함수인 _tcslwr()로 대체
		_tcscpy(cmdTokenList[tokenNum++], _tcslwr(token));
		//cmdString에서 seps(" ,\l\n"))를 구분자로 다음 문자열 불러오기
		token = _tcstok(NULL, seps);
	}

	return tokenNum;
}


int CmdProcessing(int tokenNum) {
	TCHAR ERROR_CMD[] = _T("'%s'은(는) 실행할 수 있는 프로그램이 아닙니다.\n");

	BOOL isRun;
	STARTUPINFO si = { 0, };
	PROCESS_INFORMATION pi;
	si.cb = sizeof(si);

	TCHAR cmdStringWithOptions[STR_LEN] = { 0, };
	TCHAR optString[STR_LEN] = { 0, };

	if (!_tcscmp(cmdTokenList[0], _T("exit"))) {
		return TRUE;
	}
	else if (!_tcscmp(cmdTokenList[0], _T("echo"))) {
		//입력된 문자열을 하나의 string으로 구성, 그대로 출력
		for (int i = 1; i < tokenNum; i++) {
			_stprintf(optString, _T("%s %s"), optString, cmdTokenList[i]);
		}
		_tprintf(_T("echo message : %s \n"), optString);
	}
	else if (!_tcscmp(cmdTokenList[0], _T("start"))) {
		//start 외 추가 문자열 처리 (예시: start echo hello u of sw)
		if (tokenNum > 1) {
			for (int i = 1; i < tokenNum; i++) {
				_stprintf(optString, _T("%s %s"), optString, cmdTokenList[i]);
			}
			_stprintf(cmdStringWithOptions, _T("%s %s"), _T("ch04_cmdPrompt.exe"), optString);
		}
		else {
			//start만 입력된 경우
			_stprintf(cmdStringWithOptions, _T("%s"), _T("ch04_cmdPrompt.exe"));
		}
		isRun = CreateProcess(NULL, cmdStringWithOptions, NULL, NULL, TRUE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi);
		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);
	}
	else {
		_tcscpy(cmdStringWithOptions, cmdTokenList[0]);
		for (int i = 1; i < tokenNum; i++) {
			_stprintf(cmdStringWithOptions, _T("%s %s"), cmdStringWithOptions, cmdTokenList[i]);
		}

		isRun = CreateProcess(NULL, cmdStringWithOptions, NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi);

		if (isRun == FALSE)
			_tprintf(ERROR_CMD, cmdTokenList[0]);
		//Wait until child process exits.
		WaitForSingleObject(pi.hProcess, INFINITE);
		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);
	}

	return 0;
}