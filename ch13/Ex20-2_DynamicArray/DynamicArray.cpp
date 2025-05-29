/*
* 구조적 예외처리(SEH) 기반 Dynamic Array 구현
*/

#include <stdio.h>
#include <tchar.h>
#include <windows.h>

#define MAX_PAGE 10 // 할당할 최대 페이지 수

int* nextPageAddr;	// 다음에 할당할 페이지 시작 주소
DWORD pageCnt = 0;	// 현재까지 commit된 페이지 수
DWORD pageSize;		// 시스템의 페이지 크기 (보통 4KB)

int PageFaultExceptionFilter(DWORD);

int _tmain(int argc, TCHAR* argv[])
{
	LPVOID baseAddr;
	int* lpPtr;
	SYSTEM_INFO sSysInfo;
	GetSystemInfo(&sSysInfo);		// 페이지 크기 확보
	pageSize = sSysInfo.dwPageSize; // pageSize 변수에 페이지 크기 대입

	/*
	* MAX_PAGE의 개수만큼 페이지 예약
	* PAGE_NOACCESS로 설정했기 때문에, 실제 접근 시 예외 발생
	* 아래 try, catch문 참고
	*/
	baseAddr = VirtualAlloc(
		NULL,					// 시스템이 알아서 임의 주소 할당
		MAX_PAGE * pageSize,	// 예약 메모리 크기 (10개 페이지 예약)
		MEM_RESERVE,			// Reserve (예약)
		PAGE_NOACCESS			// PAGE_NOACCESS 설정으로 접근 시 예외 발생 (SEH 활용 위해)
	);			
	
	if (baseAddr == NULL)
		_tprintf(_T("VirtualAlloc reserve failed! \n"));
	
	lpPtr = (int*)baseAddr;			// 배열의 시작 번지와 같은 의미 부여
	nextPageAddr = (int*)baseAddr;
	
	// 배열 접근 시 할당되지 않은 페이지에 접근 -> fage fault 예외 발생
	// 예외를 발생시키는 반복 개념
	for (int i = 0; i < (MAX_PAGE * pageSize) / sizeof(int); i++) {
		__try {
			lpPtr[i] = i;
		}
		// 예외 필터 함수 PageFaultExceptionFilter() 사용
		// PageFaultExceptionFilter() 함수 내부에서 실제 메모리 할당
		__except (PageFaultExceptionFilter(GetExceptionCode())) {
			ExitProcess(GetLastError()); // 예외처리 문제 발생 시 종료
		}
	}
	// 모든 예약된 페이지와 물리 메모리를 한 번에 해제
	BOOL isSuccess = VirtualFree(
		baseAddr,		// 해제할 메모리의 시작 번지
		0,				// 반드시 0으로 설정해야 함, 주소는 반드시 예약 시작 주소여야 함
		MEM_RELEASE);	// Free 상태로 변경
	
	if (isSuccess)
		_tprintf(_T("Release succeeded! \n"));
	else
		_tprintf(_T("Release failed \n"));
	return 1;
}

/*
* 배열 요소에 접근했을 때 아직 물리 메모리가 할당되지 않아서
* EXCEPTION_ACCESS_VIOLATION 예외가 발생하면
* 그 위치에 메모리를 할당(MEM_COMMIT)해주는 역할
*/
int PageFaultExceptionFilter(DWORD exptCode)
{
	// 예외가 접근 위반(= page fault)가 아니라면 예외 종료
	// 즉, 의도한 예외가 아니라면 그냥 종료
	if (exptCode != EXCEPTION_ACCESS_VIOLATION) {
		_tprintf(_T("Exception code = %d\n"), exptCode);
		return EXCEPTION_EXECUTE_HANDLER;
	}
	_tprintf(_T("Exception is a page fault \n")); // 할당된 메모리가 없다
	
	// 최대 가능 할당 페이지 수를 넘어가면 더 이상 할당하지 않고 종료
	if (pageCnt >= MAX_PAGE) {
		_tprintf(_T("Exception: out of page \n"));
		return EXCEPTION_EXECUTE_HANDLER;
	}

	// 아직 Commit되지 않은 주소에 대해 실제 메모리를 할당
	LPVOID lpvResult = VirtualAlloc(
		(LPVOID)nextPageAddr,	// 다음 페이지 주소
		pageSize,				// 페이지 크기
		MEM_COMMIT,				// 실제 물리 메모리 할당
		PAGE_READWRITE			// 읽기/쓰기 허용
	);
	
	// 할당 실패 시 종료
	if (lpvResult == NULL) {
		_tprintf(_T("VirtualAlloc failed! \n"));
		return EXCEPTION_EXECUTE_HANDLER;
	}
	else {
		_tprintf(_T("Allocating another page. \n"));
	}
	pageCnt++;	// 성공 시 pageCnt++ 하면서 다음 페이지로 이동

	// nextPageAddr는 int* 타입이므로, 바이트 단위 크기인 pageSize를 sizeof(int)로 나눠서 인덱스 이동
	nextPageAddr += pageSize / sizeof(int); // 주소는 int 단위로 증가/감소 (pageSize는 byte단위)

		// 예외 발생한 코드(즉, 배열 접근한 그 지점)으로 다시 돌아가서 실행 계속
		return EXCEPTION_CONTINUE_EXECUTION;
}