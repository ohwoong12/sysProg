#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<tchar.h>
#include<Windows.h>

int _tmain(int argc, TCHAR* argv[]) {
	HANDLE hProcess;
	TCHAR cmdString[1024];

	//DuplicateHandle(GetCurrentProcess(), GetCurrentProcess(), GetCurrentProcess(), &hProcess, 0, TRUE, DUPLICATE_SAME_ACCESS);
	DuplicateHandle(
		GetCurrentProcess(),        // �ҽ� ���μ���
		GetCurrentProcess(),        // ������ �ڵ� (�ڽ��� ���μ��� �ڵ�)
		GetCurrentProcess(),        // Ÿ�� ���μ��� (���⼭�� �ڱ� �ڽ�)
		&hProcess,                  // ��� �ڵ�
		0,                          // ���� ���� (0�̸� ������ ����)
		TRUE,                       // �ڵ� ��� �����ϰ�
		DUPLICATE_SAME_ACCESS       // ���� ���� �������� ����
	);
	_stprintf(cmdString, _T("%s %u"), _T("Ex8-4_DHChildProcess.exe"), (unsigned)hProcess);
	_tprintf(_T("hProcess : %d \n"), hProcess);

	STARTUPINFO si = { 0, };
	PROCESS_INFORMATION pi = { 0, };

	si.cb = sizeof(si);

	BOOL isSuccess = CreateProcess(NULL, cmdString, NULL, NULL, TRUE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi);

	if (isSuccess == FALSE) {
		_tprintf(_T("CreateProcess failed \n"));
		return -1;
	}

	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);

	_tprintf(_T("[Parent Process]\n"));
	_tprintf(_T("Press any key to exit!\n"));
	_gettch();

	return 0;
}
