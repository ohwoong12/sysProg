/*
SystemInfo.cpp
프로그램 설명 : Windows 시스템의 페이지 및 AGB 크기 정보 확인
*/

#include <stdio.h>
#include <tchar.h>
#include <windows.h>

int _tmain(int argc, TCHAR argv[])
{
	SYSTEM_INFO si;			// SYSTEM_INFO 구조체 선언
	DWORD alloGranularity;
	DWORD pageSize;			// 할당 정렬 단위 (AGB), 일반적으로 64KB

	GetSystemInfo(&si);	// 시스템 정보를 얻기 위하여 호출
	
	// SYSTEM_INFO 구조체에서 페이지 크기와 할당 단위를 추출
	pageSize = si.dwPageSize;
	alloGranularity = si.dwAllocationGranularity;

	// 페이지 크기와 할당 단위를 KB 단위로 출력
	_tprintf(_T("Page Size : %u Kbytes\n"), pageSize/1024);
	_tprintf(_T("Allocation Granularity : % u Kbytes \n"),alloGranularity / 1024);
	
	return 0;
}