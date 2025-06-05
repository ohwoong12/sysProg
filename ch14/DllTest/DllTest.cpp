#include <stdio.h>
#include <tchar.h>

#pragma comment(lib, "SwapDll.lib")

//#include "SwapDll.h"
_declspec(dllimport) void swap(int* v1, int* v2);

int _tmain(int argc, TCHAR* argv[])
{
	int a = 3000;
	int b = 8000;
	
	_tprintf(_T("Before : %d %d \n"), a, b);
	swap(&a, &b);
	_tprintf(_T("After : %d %d \n"), a, b);

	return 1;
}
