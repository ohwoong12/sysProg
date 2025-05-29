/*
SystemInfo.cpp
���α׷� ���� : Windows �ý����� ������ �� AGB ũ�� ���� Ȯ��
*/

#include <stdio.h>
#include <tchar.h>
#include <windows.h>

int _tmain(int argc, TCHAR argv[])
{
	SYSTEM_INFO si;			// SYSTEM_INFO ����ü ����
	DWORD alloGranularity;
	DWORD pageSize;			// �Ҵ� ���� ���� (AGB), �Ϲ������� 64KB

	GetSystemInfo(&si);	// �ý��� ������ ��� ���Ͽ� ȣ��
	
	// SYSTEM_INFO ����ü���� ������ ũ��� �Ҵ� ������ ����
	pageSize = si.dwPageSize;
	alloGranularity = si.dwAllocationGranularity;

	// ������ ũ��� �Ҵ� ������ KB ������ ���
	_tprintf(_T("Page Size : %u Kbytes\n"), pageSize/1024);
	_tprintf(_T("Allocation Granularity : % u Kbytes \n"),alloGranularity / 1024);
	
	return 0;
}