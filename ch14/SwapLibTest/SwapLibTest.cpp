// SwapLibTest.cpp
#include <stdio.h>
#include <tchar.h>

#pragma comment(lib, "SwapStaticLib.lib")

void swap(int* v1, int* v2);

int _tmain(int argc, TCHAR* argv[])
{
	int a = 50;
	int b = 100;

	_tprintf(_T("Before : %d %d \n"), a, b);
	swap(&a, &b);
	_tprintf(_T("After : %d %d \n"), a, b);
	
	return 0;
}