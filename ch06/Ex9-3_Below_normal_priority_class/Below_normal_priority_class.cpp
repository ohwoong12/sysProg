/*
	below_normal_priority_class.cpp (bpriority.exe)
	프로그램 설명 : 단순 출력 프로그램
*/

#include <stdio.h>
#include <tchar.h>
#include <windows.h>

int _tmain(int argc, TCHAR* argv[]) {
	SetPriorityClass(GetCurrentProcess(), BELOW_NORMAL_PRIORITY_CLASS);

	int count = 0;
	while (1) {
		for (DWORD i = 0; i < 10000; i++)
			for (DWORD j = 0; j < 10000; j++);
		if (count++ == 10)
			break;
		_fputts(_T("BELOW_NORMAL_PRIORITY_CLASS process is running \n"), stdout);
	}

	return 0;
}