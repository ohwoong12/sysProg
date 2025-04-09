#include <stdio.h>
#include <tchar.h>
#include <windows.h>
int _tmain(int argc, TCHAR* argv[])
{
	STARTUPINFO siNormal = { 0, };
	PROCESS_INFORMATION piNormal;
	TCHAR commandOne[] = _T("Ex9-2_Normal_priority_class.exe");
	STARTUPINFO siBelow = { 0, };
	PROCESS_INFORMATION piBelow;
	TCHAR commandTwo[] = _T("Ex9-3_Below_normal_priority_class.exe");

	siNormal.cb = sizeof(siNormal);
	siBelow.cb = sizeof(siBelow);
	
	SetPriorityClass(GetCurrentProcess(), ABOVE_NORMAL_PRIORITY_CLASS);
	
	CreateProcess(NULL, commandOne, NULL, NULL, TRUE, 0, NULL, NULL, &siNormal, &piNormal);
	CreateProcess(NULL, commandTwo, NULL, NULL,	TRUE, 0, NULL, NULL, &siBelow, &piBelow);

	int count = 0;
	while (1) {
		for (DWORD i = 0; i < 10000; i++)
			for (DWORD j = 0; j < 10000; j++);

		if (count++ == 10)
			break;

		_fputts(_T("ABOVE_NORMAL_PRIORITY_CLASS process is running \n"), stdout);
	}

	return 0;
}