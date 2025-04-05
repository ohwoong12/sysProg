/*Operation1.cpp*/
#include<stdio.h>
#include<tchar.h>
#include<Windows.h>

int _tmain(int argc, TCHAR* argv[]) {
	STARTUPINFO si = { 0, };
	PROCESS_INFORMATION pi;
	si.cb = sizeof(si);
	TCHAR command[] = _T("Ex6-2_Operation2.exe");

	CreateProcess(NULL, command, NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi);

	DWORD count = 0;
	while (count < 10) {
		for (DWORD i = 0; i < 10000; i++) {
			for (DWORD j = 0; j < 10000; j++);	//Busy Waiting!!
		}
		_fputts(_T("Operation1.exe \n"), stdout);
		count++;
	}
	return 0;
}