/*Operation2.cpp*/
#include<stdio.h>
#include<tchar.h>
#include<Windows.h>

int _tmain(int argc, TCHAR* argv[]) {
	SetPriorityClass(GetCurrentProcess(), HIGH_PRIORITY_CLASS);

	DWORD count = 0;
	while (count < 10) {
		for (DWORD i = 0; i < 10000; i++)
			for (DWORD j = 0; j < 10000; j++);
		_fputts(_T("Ex6-2_Operation2.exe \n"), stdout);
		count++;
	}
	return 0;
}