/*
GetFullPathName.cpp
���α׷� ���� : �����̸� ������� ������� ������
*/
#include <stdio.h>
#include <tchar.h>
#include <windows.h>
#include <locale.h>

#define STRING_LEN 100

int _tmain(int argc, TCHAR* argv[])
{
	_tsetlocale(LC_ALL, _T("korean"));

	TCHAR fileName[] = _T("���� ������Ʈ.txt");
	TCHAR fileFullPath[STRING_LEN];
	LPTSTR filePtr;
	
	GetFullPathName(fileName, STRING_LEN, fileFullPath, &filePtr);
	
	_tprintf(_T("%s \n"), fileFullPath);
	_tprintf(_T("%s \n"), filePtr);
	
	return 0;
}