/*
UseDll.cpp
프로그램 설명 : DLL 참조하는 프로그램
*/
#include <stdio.h>
#include <tchar.h>
#include "Calculator.h"

// calculator_dll.lib와 calculator_dll.dll을 프로젝트 folder에 넣어야 함
#pragma comment(lib, "calculator_dll.lib")

int _tmain(int argc, TCHAR* argv[])
{
	_tprintf(_T("result Add: %d \n"), Add(5, 3));
	_tprintf(_T("result Min: %d \n"), Min(5, 3));
	_tprintf(_T("result Mul: %e \n"), Mul(5.0, 3.0));
	_tprintf(_T("result Div: %e \n"), Div(5.0, 3.0));
	return 1;
}