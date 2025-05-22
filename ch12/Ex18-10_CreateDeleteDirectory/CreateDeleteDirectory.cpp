/*
CreateDeleteDirectory.cpp
���α׷� ���� : ���͸��� ������ �Ҹ�
*/
#include <stdio.h>
#include <tchar.h>
#include <windows.h>

// 1�̸� ���丮 ����, 0�̸� ���丮 ����
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