#include<stdio.h>
#include<tchar.h>
#include<Windows.h>

int _tmain(int argc, TCHAR* argv[]) {
	STARTUPINFO si = { 0, };
	PROCESS_INFORMATION pi;
	si.cb = sizeof(si);

	TCHAR command[] = _T("Ex6-2_Operation2.exe");
	//TCHAR command2[] = _T("calc.exe");
	CreateProcess(NULL, command, NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi);	//CreateProcess로 Operation2.exe 자신의 우선순위를 높임
	//CreateProcess(NULL, command2, NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi);

	DWORD timing = 0;
	while (1) {	
		for (DWORD i = 0; i < 10000; i++)
			for (DWORD j = 0; j < 10000; j++);	//Busy Waiting!!

		_fputts(_T("Parent \n"), stdout);

		timing += 1;
		if (timing == 2)
			// 새로 생성된 프로세스의 핸들 pi.hProcess을 통해 Ex6-3_kernelObjectShare.exe는 Ex6-2_Operation2.exe의 우선순위를 보통으로 낮춤
			SetPriorityClass(pi.hProcess, NORMAL_PRIORITY_CLASS);	
	}
	return 0;
}