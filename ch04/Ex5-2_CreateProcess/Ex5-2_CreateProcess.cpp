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

	GetCurrentDirectory(DIR_LEN, cDir);	//���� ���丮 Ȯ��
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

#define DIR_LEN MAX_PATH+1	//MAX_PATH�� windef.h�� ����Ǿ� �ִµ� windows���� ����ϴ� ��������� �ִ� ���̰� ������ �˷���

int _tmain(int argck, TCHAR* argv[]) {
	STARTUPINFO si = { 0, };	// STARTUPINFO ����ü ������ ����� ���ÿ� 0���� �ʱ�ȭ, �� ������ CreateProcess�Լ��� 9��° ���ڷ� ���� ��ҷμ�
	// �����ϴ� ���μ����� �Ӽ��� �����ϴ� �뵵�� ���ȴ�, ������ 0���� �ʱ�ȭ �ؾ���.
	PROCESS_INFORMATION pi;
	TCHAR title[] = _T("AdderProcess.exe 10 20");

	si.cb = sizeof(si);	// ����ü ���� si�� ����Ʈ ���� ũ��� ������� cb�� �ʱ�ȭ�ϰ� ����.
	si.dwFlags = STARTF_USEPOSITION | STARTF_USESIZE;	// si ����ü ������ �����Ǿ� �ִ� ���� �߿��� �ݿ����� �ϴ� ����鿡 ���� ������ ����.
	// STARTF_USEPOSITION: ����ü ��� �߿��� dwX�� dwY���� �����ؼ�, �����ϴ� ���μ��� ������ ��ġ�� ������ �� ���ȴ�.
	// ���� �ƹ��� dwX, dwY ���� ������ �ִ��� dwFlags�� STARTF_USEPOSITION�� �������� ������ �ƹ� �ǹ̰� ����
	si.dwX = 100;	// ���μ��� �������� x ��ǥ
	si.dwY = 200;	// ���μ��� �������� y ��ǥ
	si.dwXSize = 300;	// ���μ��� �������� ���� ����	
	si.dwYSize = 200;	// ���μ��� �������� ���� ����
	si.lpTitle = title;	// ������ ���ڿ��� ���μ��� �������� Ÿ��Ʋ �� ������ ������ �� ����.

	TCHAR command[] = _T("ch04_Ex5_1_AddressProcess.exe");	// �� ���α׷��� ����
	TCHAR cDir[DIR_LEN];
	BOOL state;

	GetCurrentDirectory(DIR_LEN, cDir);	// ���� ���丮 Ȯ��
	_fputts(cDir, stdout);
	_fputts(_T("\n"), stdout);

	SetCurrentDirectory(_T("C:\\WinSystem"));	// ���� ���͸��� C:\\WinSystem ���� ����

	GetCurrentDirectory(DIR_LEN, cDir);	//���� ���丮 Ȯ��
	_fputts(cDir, stdout);
	_fputts(_T("\n"), stdout);


	//ù ��° �������� : NULL, �� ��° ���ڸ� ���ؼ� �����Ϸ��� ���μ��� �̸� �������� �Բ� ���� ����
	state = CreateProcess(NULL, command, NULL, NULL, TRUE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi);	// �̷��� �ʱ�ȭ �� ����ü ���� si�� ���ڷ� ���޵ǰ� ����.

	if (state != 0)
		_fputts(_T("Creation OK!! \n"), stdout);	// ���丮 Ȯ��
	else
		_fputts(_T("Creation Error!! \n"), stdout);

	return 0;
}