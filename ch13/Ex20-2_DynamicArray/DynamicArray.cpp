#include <stdio.h>
#include <tchar.h>
#include <windows.h>

#define MAX_PAGE 10 //�Ҵ��� �ִ� ������ ��

int* nextPageAddr;	// ������ �Ҵ��� ������ ���� �ּ�
DWORD pageCnt = 0;	// ������� commit�� ������ ��
DWORD pageSize;		// �ý����� ������ ũ�� (���� 4KB)

int PageFaultExceptionFilter(DWORD);

int _tmain(int argc, TCHAR* argv[])
{
	LPVOID baseAddr;
	int* lpPtr;
	SYSTEM_INFO sSysInfo;
	GetSystemInfo(&sSysInfo);
	pageSize = sSysInfo.dwPageSize; // �ý����� ����ϴ� ������ ũ�⸦ �˾Ƴ�
	
	// MAX_PAGE�� ������ŭ ������ ����
	// PAGE_NOACCESS�� �����߱� ������, ���� ���� �� ���� �߻�
	// �Ʒ� try, catch�� ����
	baseAddr = VirtualAlloc(
		NULL, // ���� �ּ� �Ҵ�
		MAX_PAGE * pageSize,// ���� �޸� ũ�� (10�� ������ ����)
		MEM_RESERVE, // Reserve (����)
		PAGE_NOACCESS); // NO_ACCESS
	
	if (baseAddr == NULL)
		_tprintf(_T("VirtualAlloc reserve failed! \n"));
	
	lpPtr = (int*)baseAddr; // �迭�� ���� ������ ���� �ǹ� �ο�
	nextPageAddr = (int*)baseAddr;
	
	// page fault �߻� �� ���� �߻�
	// ���ܸ� �߻���Ű�� �ݺ� ����
	for (int i = 0; i < (MAX_PAGE * pageSize) / sizeof(int); i++) {
		__try {
			lpPtr[i] = i;
		}
		// ���� ���� �Լ� PageFaultExceptionFilter() ���
		__except (PageFaultExceptionFilter(GetExceptionCode())) {
			ExitProcess(GetLastError()); // ����ó�� ���� �߻� �� ����
		}
	}

	BOOL isSuccess = VirtualFree(
		baseAddr, // ������ �޸��� ���� ����
		0, // �ݵ�� 0���� �����ؾ� �� (VirtualFree - MEM_RELEASE����)
		MEM_RELEASE); // Free ���·� ����
	if (isSuccess)
		_tprintf(_T("Release succeeded! \n"));
	else
		_tprintf(_T("Release failed \n"));
	return 1;
}

int PageFaultExceptionFilter(DWORD exptCode)
{
	// �޸� ���� ������ �ƴ϶�� �׳� ����
	if (exptCode != EXCEPTION_ACCESS_VIOLATION) {
		_tprintf(_T("Exception code = %d\n"), exptCode);
		return EXCEPTION_EXECUTE_HANDLER;
	}
	_tprintf(_T("Exception is a page fault \n")); // �Ҵ�� �޸𸮰� ����
	if (pageCnt >= MAX_PAGE) {
		_tprintf(_T("Exception: out of page \n"));
		return EXCEPTION_EXECUTE_HANDLER;
	}
	// �޸� �Ҵ�
	LPVOID lpvResult = VirtualAlloc((LPVOID)nextPageAddr, pageSize, MEM_COMMIT, PAGE_READWRITE);
	if (lpvResult == NULL) {
		_tprintf(_T("VirtualAlloc failed! \n"));
		return EXCEPTION_EXECUTE_HANDLER;
	}
	else {
		_tprintf(_T("Allocating another page. \n"));
	}
	pageCnt++;
	nextPageAddr += pageSize / sizeof(int); // �ּҴ� int ������ ����/���� (pageSize�� byte����)
		// page fault�� �߻��� �������� ���ư��� ���� ���
		return EXCEPTION_CONTINUE_EXECUTION;
}