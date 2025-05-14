/*
exceptionfinally.cpp
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <tchar.h>
#include <windows.h>

int _tmain(int argc, TCHAR* argv[]) {
	TCHAR str[2];

	__try {
		_tcscpy(str, _T("ABCDEFGHI~"));
		_tprintf(_T("%s \n"), str);
	}
	__finally {
		_tprintf(_T("__finally block! \n"));
	}

	return 0;
}