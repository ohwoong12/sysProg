#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <tchar.h>
#include <windows.h>

int _tmain(int argc, TCHAR* argv[])
{
	// 시스템의 페이지 크기를 가져와서, 이후 힙 생성 시 크기 단위로 사용
	SYSTEM_INFO si;
	GetSystemInfo(&si);
	UINT pageSize = si.dwPageSize;
	
	/*
	* HEAP_NO_SERIALIZE: 동기화 비활성화 (단일 쓰레드용 성능 최적화)
	* 초기 커밋 크기: 10페이지 (40KB)
	* 최대 힙 크기: 100페이지 (400KB)
	*/
	HANDLE hHeap = HeapCreate(HEAP_NO_SERIALIZE, pageSize * 10, pageSize * 100);
	
	/*
	* 사용자 정의 힙에서 int 10개를 담을 공간 할당
	* 즉, 40바이트 할당
	*/
	int* p = (int*)HeapAlloc(hHeap, HEAP_NO_SERIALIZE, sizeof(int) * 10);

	// 메모리에 값 저장 후 출력
	for (int i = 0; i < 10; i++) {
		p[i] = i;
		_tprintf(_T("contents in memory created in newly created a Heap: % d \n"), p[i]);
	}

	// 사용자 힙 메모리 해제
	HeapFree(hHeap, 0, p);

	// 힙 소멸 HeapDestroy(hHeap);
	HANDLE hDefaultHeap = GetProcessHeap();	// GetProcessHeap()로 디폴트 힙 핸들 
	// 문자열을 위한 메모리 50 TCHAR 크기만큼 할당
	TCHAR* pDefault = (TCHAR*)HeapAlloc(hDefaultHeap, HEAP_NO_SERIALIZE, sizeof(TCHAR) * 50);
	_tcscpy(pDefault, _T("\nA test of allocation of memory in Default Heap!\n"));	// 문자열 복사 후 출력
	_tprintf(_T("%s"), pDefault);

	// 메모리 해제
	HeapFree(hDefaultHeap, HEAP_NO_SERIALIZE, pDefault);
	HeapDestroy(hHeap);	// 명시적으로 힙을 제거해야 전체 힙 메모리가 제거 됨	
	return 1;
}