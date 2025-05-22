/*
SystemWindowsDir.cpp
���α׷� ���� : �ý��� ���͸��� Windows ���͸� Ȯ��
*/
#include <stdio.h>
#include <tchar.h>
#include <windows.h>

int _tmain(int argc, TCHAR* argv[])
{
	// 2���� ���۸� ����(TCHAR�� �����ڵ�� ��Ƽ����Ʈ ȣȯ)
	// MAX_PATH�� Windows������ ��� �ִ� ����
	TCHAR sysPathBuff[MAX_PATH];
	TCHAR winPathBuff[MAX_PATH];
	
	GetSystemDirectory(sysPathBuff, MAX_PATH);	// �ý��� ���丮 ��θ� sysPathBuff�� ����
	GetWindowsDirectory(winPathBuff, MAX_PATH);	// Windows ��ġ ��θ� winPathBuff�� ����
	
	_tprintf(_T("System directory : %s \n"), sysPathBuff);
	_tprintf(_T("Windows directory : %s \n"), winPathBuff);
	
	return 0;
}