/*
* ������ ����ó��(SEH) ��� Dynamic Array ����
*/

#include <stdio.h>
#include <tchar.h>
#include <windows.h>

#define MAX_PAGE 10 // �Ҵ��� �ִ� ������ ��

int* nextPageAddr;	// ������ �Ҵ��� ������ ���� �ּ�
DWORD pageCnt = 0;	// ������� commit�� ������ ��
DWORD pageSize;		// �ý����� ������ ũ�� (���� 4KB)

int PageFaultExceptionFilter(DWORD);

int _tmain(int argc, TCHAR* argv[])
{
	LPVOID baseAddr;
	int* lpPtr;
	SYSTEM_INFO sSysInfo;
	GetSystemInfo(&sSysInfo);		// ������ ũ�� Ȯ��
	pageSize = sSysInfo.dwPageSize; // pageSize ������ ������ ũ�� ����

	/*
	* MAX_PAGE�� ������ŭ ������ ����
	* PAGE_NOACCESS�� �����߱� ������, ���� ���� �� ���� �߻�
	* �Ʒ� try, catch�� ����
	*/
	baseAddr = VirtualAlloc(
		NULL,					// �ý����� �˾Ƽ� ���� �ּ� �Ҵ�
		MAX_PAGE * pageSize,	// ���� �޸� ũ�� (10�� ������ ����)
		MEM_RESERVE,			// Reserve (����)
		PAGE_NOACCESS			// PAGE_NOACCESS �������� ���� �� ���� �߻� (SEH Ȱ�� ����)
	);			
	
	if (baseAddr == NULL)
		_tprintf(_T("VirtualAlloc reserve failed! \n"));
	
	lpPtr = (int*)baseAddr;			// �迭�� ���� ������ ���� �ǹ� �ο�
	nextPageAddr = (int*)baseAddr;
	
	// �迭 ���� �� �Ҵ���� ���� �������� ���� -> fage fault ���� �߻�
	// ���ܸ� �߻���Ű�� �ݺ� ����
	for (int i = 0; i < (MAX_PAGE * pageSize) / sizeof(int); i++) {
		__try {
			lpPtr[i] = i;
		}
		// ���� ���� �Լ� PageFaultExceptionFilter() ���
		// PageFaultExceptionFilter() �Լ� ���ο��� ���� �޸� �Ҵ�
		__except (PageFaultExceptionFilter(GetExceptionCode())) {
			ExitProcess(GetLastError()); // ����ó�� ���� �߻� �� ����
		}
	}
	// ��� ����� �������� ���� �޸𸮸� �� ���� ����
	BOOL isSuccess = VirtualFree(
		baseAddr,		// ������ �޸��� ���� ����
		0,				// �ݵ�� 0���� �����ؾ� ��, �ּҴ� �ݵ�� ���� ���� �ּҿ��� ��
		MEM_RELEASE);	// Free ���·� ����
	
	if (isSuccess)
		_tprintf(_T("Release succeeded! \n"));
	else
		_tprintf(_T("Release failed \n"));
	return 1;
}

/*
* �迭 ��ҿ� �������� �� ���� ���� �޸𸮰� �Ҵ���� �ʾƼ�
* EXCEPTION_ACCESS_VIOLATION ���ܰ� �߻��ϸ�
* �� ��ġ�� �޸𸮸� �Ҵ�(MEM_COMMIT)���ִ� ����
*/
int PageFaultExceptionFilter(DWORD exptCode)
{
	// ���ܰ� ���� ����(= page fault)�� �ƴ϶�� ���� ����
	// ��, �ǵ��� ���ܰ� �ƴ϶�� �׳� ����
	if (exptCode != EXCEPTION_ACCESS_VIOLATION) {
		_tprintf(_T("Exception code = %d\n"), exptCode);
		return EXCEPTION_EXECUTE_HANDLER;
	}
	_tprintf(_T("Exception is a page fault \n")); // �Ҵ�� �޸𸮰� ����
	
	// �ִ� ���� �Ҵ� ������ ���� �Ѿ�� �� �̻� �Ҵ����� �ʰ� ����
	if (pageCnt >= MAX_PAGE) {
		_tprintf(_T("Exception: out of page \n"));
		return EXCEPTION_EXECUTE_HANDLER;
	}

	// ���� Commit���� ���� �ּҿ� ���� ���� �޸𸮸� �Ҵ�
	LPVOID lpvResult = VirtualAlloc(
		(LPVOID)nextPageAddr,	// ���� ������ �ּ�
		pageSize,				// ������ ũ��
		MEM_COMMIT,				// ���� ���� �޸� �Ҵ�
		PAGE_READWRITE			// �б�/���� ���
	);
	
	// �Ҵ� ���� �� ����
	if (lpvResult == NULL) {
		_tprintf(_T("VirtualAlloc failed! \n"));
		return EXCEPTION_EXECUTE_HANDLER;
	}
	else {
		_tprintf(_T("Allocating another page. \n"));
	}
	pageCnt++;	// ���� �� pageCnt++ �ϸ鼭 ���� �������� �̵�

	// nextPageAddr�� int* Ÿ���̹Ƿ�, ����Ʈ ���� ũ���� pageSize�� sizeof(int)�� ������ �ε��� �̵�
	nextPageAddr += pageSize / sizeof(int); // �ּҴ� int ������ ����/���� (pageSize�� byte����)

		// ���� �߻��� �ڵ�(��, �迭 ������ �� ����)���� �ٽ� ���ư��� ���� ���
		return EXCEPTION_CONTINUE_EXECUTION;
}