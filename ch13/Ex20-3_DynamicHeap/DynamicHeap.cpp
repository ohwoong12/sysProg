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
	HANDLE hHeap = HeapCreate(HEAP_NO_SERIALIZE, pageSize * 10, pageSize * 100);
	
	/*
	* ����� ���� ������ int 10���� ���� ���� �Ҵ�
	* ��, 40����Ʈ �Ҵ�
	*/
	int* p = (int*)HeapAlloc(hHeap, HEAP_NO_SERIALIZE, sizeof(int) * 10);

	// �޸𸮿� �� ���� �� ���
	for (int i = 0; i < 10; i++) {
		p[i] = i;
		_tprintf(_T("contents in memory created in newly created a Heap: % d \n"), p[i]);
	}

	// ����� �� �޸� ����
	HeapFree(hHeap, 0, p);

	// �� �Ҹ� HeapDestroy(hHeap);
	HANDLE hDefaultHeap = GetProcessHeap();	// GetProcessHeap()�� ����Ʈ �� �ڵ� 
	// ���ڿ��� ���� �޸� 50 TCHAR ũ�⸸ŭ �Ҵ�
	TCHAR* pDefault = (TCHAR*)HeapAlloc(hDefaultHeap, HEAP_NO_SERIALIZE, sizeof(TCHAR) * 50);
	_tcscpy(pDefault, _T("\nA test of allocation of memory in Default Heap!\n"));	// ���ڿ� ���� �� ���
	_tprintf(_T("%s"), pDefault);

	// �޸� ����
	HeapFree(hDefaultHeap, HEAP_NO_SERIALIZE, pDefault);
	HeapDestroy(hHeap);	// ��������� ���� �����ؾ� ��ü �� �޸𸮰� ���� ��	
	return 1;
}