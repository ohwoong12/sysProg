#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <tchar.h>
#include <windows.h>

int _tmain(int argc, TCHAR* argv[])
{
	// �ý����� ������ ũ�⸦ �����ͼ�, ���� �� ���� �� ũ�� ������ ���
	SYSTEM_INFO si;
	GetSystemInfo(&si);
	UINT pageSize = si.dwPageSize;
	
	/*
	* HEAP_NO_SERIALIZE: ����ȭ ��Ȱ��ȭ (���� ������� ���� ����ȭ)
	* �ʱ� Ŀ�� ũ��: 10������ (40KB)
	* �ִ� �� ũ��: 100������ (400KB)
	*/
	HANDLE hHeap = HeapCreate(
		HEAP_NO_SERIALIZE,		// ����ȭ ���� (���� ����)
		pageSize * 10,			// 10 ������ �� ��� Ŀ�� (4KB * 10 = 40KB)
		pageSize * 100			// 100 ������ �� ���� (4KB * 100 = 400KB)
	);
	
	// �̰� �׳� ���� �߰��Ѱ�
	if (hHeap == NULL) {
		_tprintf(_T("HeapCreate failed!\n"));
		return 1; // �Ǵ� ������ ���� ó��
	}


	//����� ���� ������ int 10�� ��ŭ�� �޸� �Ҵ� (40����Ʈ)	
	int* p = (int*)HeapAlloc(hHeap, HEAP_NO_SERIALIZE, sizeof(int) * 10);

	// �޸𸮿� �� ���� �� ���
	for (int i = 0; i < 10; i++) {
		p[i] = i;
		_tprintf(_T("contents in memory created in newly created a Heap: % d \n"), p[i]);
	}

	// ����� �� �޸� ����
	HeapFree(hHeap, 0, p);

	// �� �Ҹ� HeapDestroy(hHeap);
	HANDLE hDefaultHeap = GetProcessHeap();	// GetProcessHeap()�� ���� ���μ����� �⺻ �� �ڵ� ��ȯ

	// ���ڿ��� ���� �޸� 50 TCHAR ũ�⸸ŭ �Ҵ�
	TCHAR* pDefault = (TCHAR*)HeapAlloc(hDefaultHeap, HEAP_NO_SERIALIZE, sizeof(TCHAR) * 50);
	_tcscpy(pDefault, _T("\nA test of allocation of memory in Default Heap!\n"));	// ���ڿ� ���� �� ���
	_tprintf(_T("%s"), pDefault);

	// �޸� ����
	HeapFree(hDefaultHeap, HEAP_NO_SERIALIZE, pDefault);
	HeapDestroy(hHeap);	// ��������� ���� �����ؾ� ��ü �� �޸𸮰� ���� ��	
	return 1;
}