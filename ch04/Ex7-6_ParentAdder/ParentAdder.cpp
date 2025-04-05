/*
ParentAdder.cpp
���α׷� ����
1. 1~10���� �����Ͽ� ���
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

	TCHAR command1[] = _T("Ex7-4_PartAdder 1 5");	// PartAdder.exe�� ������ ���� ���ڿ� �迭 ����
	TCHAR command2[] = _T("Ex7-4_PartAdder 6 10");

	DWORD sum = 0;

	si1.cb = sizeof(si1);
	si2.cb = sizeof(si2);

	CreateProcess(NULL, command1, NULL, NULL, TRUE, 0, NULL, NULL, &si1, &pi1);	// ���μ��� ����, _tmain �Լ��� ���� ����
	CreateProcess(NULL, command2, NULL, NULL, TRUE, 0, NULL, NULL, &si2, &pi2);

	CloseHandle(pi1.hThread);	// ������� ���߿�
	CloseHandle(pi2.hThread);

	/*���� �ذ��� ���� �߰��Ǵ� �� ���� �ڵ�*/
	WaitForSingleObject(pi1.hProcess, INFINITE);	// �ڽ� ���μ����� ����� ������ ��ٷ� �ִ� �ڵ�
	WaitForSingleObject(pi2.hProcess, INFINITE);

	GetExitCodeProcess(pi1.hProcess, &return_val1);	// �ڽ� ���μ������� �����ϸ鼭 �����ϴ� �����ڵ带 ��� ���� �Լ� ���
	GetExitCodeProcess(pi2.hProcess, &return_val2);

	if (return_val1 == -1 || return_val2 == -1)	// �ڽ� ���μ����� ������ ���Ḧ �ߴ��� Ȯ��
		return -1;	//-1�� ��ȯ�Ǹ� �������� ����

	sum += return_val1;	// sum ������ val1�� val2 ����
	sum += return_val2;

	_tprintf(_T("total : %d \n"), sum);	// ���

	CloseHandle(pi1.hProcess);	// �� ������ �ڵ� �������ν� �ڽ����μ��� Ŀ�� ������Ʈ ���� �Ҹ�
	CloseHandle(pi2.hProcess);

	return 0;
}