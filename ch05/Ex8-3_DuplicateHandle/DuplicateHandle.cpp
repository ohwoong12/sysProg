#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<tchar.h>
#include<Windows.h>

int _tmain(int argc, TCHAR* argv[]) {
	HANDLE hProcess;
	TCHAR cmdString[1024];

	//DuplicateHandle(GetCurrentProcess(), GetCurrentProcess(), GetCurrentProcess(), &hProcess, 0, TRUE, DUPLICATE_SAME_ACCESS);
	DuplicateHandle(
		GetCurrentProcess(),        // 소스 프로세스
		GetCurrentProcess(),        // 복제할 핸들 (자신의 프로세스 핸들)
		GetCurrentProcess(),        // 타겟 프로세스 (여기서는 자기 자신)
		&hProcess,                  // 결과 핸들
		0,                          // 접근 권한 (0이면 기존과 동일)
		TRUE,                       // 핸들 상속 가능하게
		DUPLICATE_SAME_ACCESS       // 같은 접근 권한으로 복제
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
