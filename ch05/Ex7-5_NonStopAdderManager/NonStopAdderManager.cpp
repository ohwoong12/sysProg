/*
	Ex7-4 PartAdder.exe 1 5�� Ex7-4 PartAdder.exe 6 10 �̶�� ���α׷��� ���� ����
	1+2+3+4+5
	6+7+8+9+10
	=55
	
	�ڽ� ���μ����� ����Ǹ�, �θ� ���μ����� GetExitCodeProcess�� ���� ������ ���� �޾� ���� �հ� ���
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

	TCHAR command1[] = _T("Ex7-4_PartAdder.exe 1 5");
	TCHAR command2[] = _T("Ex7-4_PartAdder.exe 6 10");

	DWORD sum = 0;

	si1.cb = sizeof(si1);	// ����ü�� ũ�⸦ �ʱ�ȭ
	si2.cb = sizeof(si2);

	CreateProcess(NULL, command1, NULL, NULL, TRUE, 0, NULL, NULL, &si1, &pi1);	// ���μ��� ����
	CreateProcess(NULL, command2, NULL, NULL, TRUE, 0, NULL, NULL, &si2, &pi2);

	CloseHandle(pi1.hThread);	// ���μ����� �̹� �������̹Ƿ� ������ �ڵ��� �ʿ䰡 ���⿡ ����
	CloseHandle(pi2.hThread);

	WaitForSingleObject(pi1.hProcess, INFINITE);	// �ڽ� ���μ����� ����� ������ ���� ���
	WaitForSingleObject(pi2.hProcess, INFINITE);

	GetExitCodeProcess(pi1.hProcess, &return_val1);	// �ڽ� ���μ����� ExitProcess(�հ�)�� �����ϸ� �� ���� ��� �ڵ�
	GetExitCodeProcess(pi2.hProcess, &return_val2);

	// �ڽ� ���μ������� ���� �߻� �� ������ �ڵ� -1�� ��ȯ������ �۵��ϴ� �ڵ�
	if (return_val1 == -1 || return_val2 == -1)
		return -1; // �Լ� ȣ�� ���� �߻����� ����

	// �� �� ���� ����� �հ� ���
	sum += return_val1;
	sum += return_val2;

	_tprintf(_T("Total : %d \n"), sum);	// ��� ���

	CloseHandle(pi1.hProcess);	// ���μ��� �ڵ� �ݾƼ� �޸� ���� ����
	CloseHandle(pi2.hProcess);

	_fgetchar();	// �ٷ� �����°� ����

	return 0;
}
