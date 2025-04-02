#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<tchar.h>
#include<locale.h>
#include<windows.h>

#define STR_LEN 256
#define CMD_TOKEN_NUM 10

TCHAR ERROR_CMD[] = _T("'%s'은(는) 실행할 수 있는 프로그램이 아닙니다. \n");
TCHAR cmdString[STR_LEN];
TCHAR cmdTokenList[CMD_TOKEN_NUM][STR_LEN];
TCHAR seps[] = _T(", \t\n");

int CmdProcessing(void);	/*	함수: int CmdProcessing(void)
								기능: 명령어를 입력 받아서 해당 명령어에 지정되어 있는 기능을 수행한다.
									  exit가 입력되면 TRUE를 반환하고 이는 프로그램 종료로 이어진다. */


int _tmain(int argcf, TCHAR* argv[]) {
	_tsetlocale(LC_ALL, _T("korean"));	//한글 처리를 가능하게 함

	DWORD isExit;	//DWORD는 Double WORD의 약자로 WORD가 2배(Unsigned long)이라는 뜻
	while (1) {
		isExit = CmdProcessing();
		if (isExit == TRUE) {
			_fputts(_T("-----명령어 처리를 종료합니다.----- \n"), stdout);
			break;
		}
	}

	return 0;
}



int CmdProcessing(void) {
	_fputts(_T("USW command prompt>> "), stdout);
	_fgetts(cmdString, 256, stdin);
	
	TCHAR* token = _tcstok(cmdString, seps);
	int tokenNum = 0;

	while (token != NULL) {
		_tcscpy(cmdTokenList[tokenNum++], _tcslwr(token));
		token = _tcstok(NULL, seps);
	}

	if (!_tcscmp(cmdTokenList[0], _T("종료"))) {	//strcmp는 같으면 0반환
		return TRUE;
	}
	else if (!_tcscmp(cmdTokenList[0], _T("네이버"))) {
		system("explorer https://www.naver.com");
		//ShellExecute(NULL,NULL,_T("C://Program Files/Google/Chrome/Application/chrome.exe"), _T("https://www.naver.com"), NULL, SW_HIDE);
	}
	else if (!_tcscmp(cmdTokenList[0], _T("추가명령2"))) {}
	else {
		_tprintf(ERROR_CMD, cmdTokenList[0]);
	}

	return 0;
}