/*
GetFullPathName.cpp
프로그램 설명 : 파일이름 기반으로 완전경로 얻어오기
*/
#include <stdio.h>
#include <tchar.h>
#include <windows.h>
#include <locale.h>

#define STRING_LEN 100

int _tmain(int argc, TCHAR* argv[])
{
	_tsetlocale(LC_ALL, _T("korean"));

	TCHAR fileName[] = _T("모프 프로젝트.txt");
	TCHAR fileFullPath[STRING_LEN];
	LPTSTR filePtr;
	
	GetFullPathName(fileName, STRING_LEN, fileFullPath, &filePtr);
	
	_tprintf(_T("%s \n"), fileFullPath);
	_tprintf(_T("%s \n"), filePtr);
	
	return 0;
}