#define _CRT_SECURE_NO_WARNINGS
//pragma warning(disable:4996) 이것도 사용 가능
//wscanf 컴파일 오류 해결 선언

#include<stdio.h>
#include<tchar.h>
#include<Windows.h>

int _tmain(int argc, TCHAR* argv[])
{
	LPCTSTR str1 = _T("MBCS or WBCS 1");	//LPCSTR -> char *T
	TCHAR str2[]= _T("MBCS or WBCS 2");
	TCHAR str3[100];
	TCHAR str4[50];

	_tprintf(_T("string size: %zd \n"), sizeof(str2));		//_tprintf -> wprintf, _T -> L
	_tprintf(_T("string length: %zd \n"), _tcslen(str1));

	_fputts(_T("Input String 1: "), stdout);
	_tscanf(_T("%s"), str3);
	_fputts(_T("Input String 2: "), stdout);
	_tscanf(_T("%s"), str4);

	_tcscat(str3, str4);
	_tprintf(_T("String 1 + String 2: %s \n"), str3);

	return 0;
}