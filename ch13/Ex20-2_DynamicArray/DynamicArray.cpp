#include <stdio.h>
#include <tchar.h>
#include <windows.h>

#define MAX_PAGE 10 //할당할 최대 페이지 수

int* nextPageAddr;	// 다음에 할당할 페이지 시작 주소
DWORD pageCnt = 0;	// 현재까지 commit된 페이지 수
DWORD pageSize;		// 시스템의 페이지 크기 (보통 4KB)

int PageFaultExceptionFilter(DWORD);

int _tmain(int argc, TCHAR* argv[])
{
	LPVOID baseAddr;
	int* lpPtr;
	SYSTEM_INFO sSysInfo;
	GetSystemInfo(&sSysInfo);
	pageSize = sSysInfo.dwPageSize; // 시스템이 사용하는 페이지 크기를 알아냄
	
	// MAX_PAGE의 개수만큼 페이지 예약
	// PAGE_NOACCESS로 설정했기 때문에, 실제 접근 시 예외 발생
	// 아래 try, catch문 참고
	baseAddr = VirtualAlloc(
		NULL, // 임의 주소 할당
		MAX_PAGE * pageSize,// 예약 메모리 크기 (10개 페이지 예약)
		MEM_RESERVE, // Reserve (예약)
		PAGE_NOACCESS); // NO_ACCESS
	
	if (baseAddr == NULL)
		_tprintf(_T("VirtualAlloc reserve failed! \n"));
	
	lpPtr = (int*)baseAddr; // 배열의 시작 번지와 같은 의미 부여
	nextPageAddr = (int*)baseAddr;
	
	// page fault 발생 시 예외 발생
	// 예외를 발생시키는 반복 개념
	for (int i = 0; i < (MAX_PAGE * pageSize) / sizeof(int); i++) {
		__try {
			lpPtr[i] = i;
		}
		// 예외 필터 함수 PageFaultExceptionFilter() 사용
		__except (PageFaultExceptionFilter(GetExceptionCode())) {
			ExitProcess(GetLastError()); // 예외처리 문제 발생 시 종료
		}
	}

	BOOL isSuccess = VirtualFree(
		baseAddr, // 해제할 메모리의 시작 번지
		0, // 반드시 0으로 설정해야 함 (VirtualFree - MEM_RELEASE에서)
		MEM_RELEASE); // Free 상태로 변경
	if (isSuccess)
		_tprintf(_T("Release succeeded! \n"));
	else
		_tprintf(_T("Release failed \n"));
	return 1;
}

int PageFaultExceptionFilter(DWORD exptCode)
{
	// 메모리 접근 오류가 아니라면 그냥 종료
	if (exptCode != EXCEPTION_ACCESS_VIOLATION) {
		_tprintf(_T("Exception code = %d\n"), exptCode);
		return EXCEPTION_EXECUTE_HANDLER;
	}
	_tprintf(_T("Exception is a page fault \n")); // 할당된 메모리가 없다
	if (pageCnt >= MAX_PAGE) {
		_tprintf(_T("Exception: out of page \n"));
		return EXCEPTION_EXECUTE_HANDLER;
	}
	// 메모리 할당
	LPVOID lpvResult = VirtualAlloc((LPVOID)nextPageAddr, pageSize, MEM_COMMIT, PAGE_READWRITE);
	if (lpvResult == NULL) {
		_tprintf(_T("VirtualAlloc failed! \n"));
		return EXCEPTION_EXECUTE_HANDLER;
	}
	else {
		_tprintf(_T("Allocating another page. \n"));
	}
	pageCnt++;
	nextPageAddr += pageSize / sizeof(int); // 주소는 int 단위로 증가/감소 (pageSize는 byte단위)
		// page fault가 발생한 지점으로 돌아가서 실행 계속
		return EXCEPTION_CONTINUE_EXECUTION;
}