#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<tchar.h>
#include<locale.h>
#include<windows.h>

#define STR_LEN 256
#define CMD_TOKEN_NUM 10

TCHAR ERROR_CMD[] = _T("'%s'��(��) ������ �� �ִ� ���α׷��� �ƴմϴ�. \n");
TCHAR cmdString[STR_LEN];
TCHAR cmdTokenList[CMD_TOKEN_NUM][STR_LEN];
TCHAR seps[] = _T(", \t\n");

int CmdProcessing(void);	/*	�Լ�: int CmdProcessing(void)
								���: ��ɾ �Է� �޾Ƽ� �ش� ��ɾ �����Ǿ� �ִ� ����� �����Ѵ�.
									  exit�� �ԷµǸ� TRUE�� ��ȯ�ϰ� �̴� ���α׷� ����� �̾�����. */


int _tmain(int argcf, TCHAR* argv[]) {
	_tsetlocale(LC_ALL, _T("korean"));	//�ѱ� ó���� �����ϰ� ��

	DWORD isExit;	//DWORD�� Double WORD�� ���ڷ� WORD�� 2��(Unsigned long)�̶�� ��
	while (1) {
		isExit = CmdProcessing();
		if (isExit == TRUE) {
			_fputts(_T("-----��ɾ� ó���� �����մϴ�.----- \n"), stdout);
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

	if (!_tcscmp(cmdTokenList[0], _T("����"))) {	//strcmp�� ������ 0��ȯ
		return TRUE;
	}
	else if (!_tcscmp(cmdTokenList[0], _T("���̹�"))) {
		system("explorer https://www.naver.com");
		//ShellExecute(NULL,NULL,_T("C://Program Files/Google/Chrome/Application/chrome.exe"), _T("https://www.naver.com"), NULL, SW_HIDE);
	}
	else if (!_tcscmp(cmdTokenList[0], _T("�߰����2"))) {}
	else {
		_tprintf(ERROR_CMD, cmdTokenList[0]);
	}

	return 0;
}