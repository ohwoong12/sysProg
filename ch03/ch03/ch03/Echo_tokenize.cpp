//���α׷� ����: exit ��ɾ� + echo ��ɾ� + tokenize()�Լ� �߰�
#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<tchar.h>
#include<locale.h>
#include<windows.h>

#define STR_LEN 256
#define CMD_TOKEN_NUM 10

TCHAR cmdString[STR_LEN];
TCHAR cmdTokenList[CMD_TOKEN_NUM][STR_LEN];
TCHAR seps[] = _T(", \t\n");
TCHAR promptMessage[STR_LEN] = _T("USW command >>");


int CmdProcessing(int);	/*	�Լ�: int CmdProcessing(void)
								���: ��ɾ �Է� �޾Ƽ� �ش� ��ɾ �����Ǿ� �ִ� ����� �����Ѵ�.
								exit�� �ԷµǸ� TRUE�� ��ȯ�ϰ� �̴� ���α׷� ����� �̾�����.	*/
int CmdTokenize(void);


int _tmain(int argc, TCHAR* argv[]) {
	_tsetlocale(LC_ALL, _T("korean"));	//�ѱ� ó���� �����ϰ� ��

	DWORD isExit = NULL;
	int tokenNum = 0;	//���α׷� main()�� �������ڰ� �ִ� ��� ���

	if (argc >= 2) {
		for (int i = 1; i < argc; i++) {
			//cmdprompt.exe. ���� string�� ù��° ��ū
			_tcscpy(cmdTokenList[i - 1], argv[i]);	//tokenize() ���
		}
		tokenNum = argc - 1;
		isExit = CmdProcessing(tokenNum);
		if (isExit == TRUE) {
			_fputts(_T("-----��ɾ� ó���� �����մϴ�----- \n"), stdout);

			return 0;
		}
	}

	while (1) {
		int tokenNum = CmdTokenize();
		if (tokenNum == 0) {	//Enter �Է� �� ó��
			continue;
		}

		isExit = CmdProcessing(tokenNum);
		
		if (isExit == TRUE) {
			_fputts(_T("-----��ɾ� ó���� �����մϴ�.----- \n"), stdout);
			break;
		}
	}

	return 0;
}

//cmd�� ���� �Է��Ǵ� string�� token(���� ���ڿ�)���� �и��ϴ� �۾�
int CmdTokenize() {
	TCHAR* token;

	_fputts(promptMessage, stdout);
	_fgetts(cmdString, 256, stdin);

	token = _tcstok(cmdString, seps);

	int tokenNum = 0;

	while (token != NULL) {	//������ ���ڿ�(token)���� cmd list �迭�� ����
		_tcscpy(cmdTokenList[tokenNum++], _tcslwr(token));
		//cmdString���� seps(" ,\l\n"))�� �����ڷ� ���� ���ڿ� �ҷ�����
		token = _tcstok(NULL, seps);
	}

	return tokenNum;
}


int CmdProcessing(int tokenNum) {
	TCHAR ERROR_CMD[] = _T("'%s'��(��) ������ �� �ִ� ���α׷��� �ƴմϴ�.\n");
	TCHAR cmdStringWithOptions[STR_LEN] = { 0, };
	TCHAR optString[STR_LEN] = { 0, };

	if (!_tcscmp(cmdTokenList[0], _T("exit"))) return TRUE;
	else if (!_tcscmp(cmdTokenList[0], _T("echo"))) {
		//�Էµ� ���ڿ��� �ϳ��� string���� ����, �״�� ���
		for (int i = 1; i < tokenNum; i++) {
			_stprintf(optString, _T("%s %s"), optString, cmdTokenList[i]);
			_tprintf(_T("echo message : %s \n"), optString);
		}
	}
	else {
		_tprintf(ERROR_CMD, cmdTokenList[0]);
	}

	return 0;
}