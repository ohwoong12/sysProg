/*
SystemWindowsDir.cpp
프로그램 설명 : 시스템 디렉터리와 Windows 디렉터리 확인
*/
#include <stdio.h>
#include <tchar.h>
#include <windows.h>

int _tmain(int argc, TCHAR* argv[])
{
	// 2개의 버퍼를 선언(TCHAR로 유니코드와 멀티바이트 호환)
	// MAX_PATH는 Windows에서의 경로 최대 길이
	TCHAR sysPathBuff[MAX_PATH];
	TCHAR winPathBuff[MAX_PATH];
	
	GetSystemDirectory(sysPathBuff, MAX_PATH);	// 시스템 디렉토리 경로를 sysPathBuff에 저장
	GetWindowsDirectory(winPathBuff, MAX_PATH);	// Windows 설치 경로를 winPathBuff에 저장
	
	_tprintf(_T("System directory : %s \n"), sysPathBuff);
	_tprintf(_T("Windows directory : %s \n"), winPathBuff);
	
	return 0;
}