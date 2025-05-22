/*
CreateDeleteDirectory.cpp
프로그램 설명 : 디렉터리의 생성과 소멸
*/
#include <stdio.h>
#include <tchar.h>
#include <windows.h>

// 1이면 디렉토리 생성, 0이면 디렉토리 삭제
#define CREATE_DIRECTORY 1

int _tmain(int argc, TCHAR* argv[])
{
	TCHAR dirRelativePath[] = _T("GDOne");
	TCHAR dirFullPath[] = _T("C:\\GDTwo");

#if CREATE_DIRECTORY
	CreateDirectory(dirRelativePath, NULL);
	CreateDirectory(dirFullPath, NULL);
#else
	RemoveDirectory(dirRelativePath);
	RemoveDirectory(dirFullPath);
#endif
	return 0;
}