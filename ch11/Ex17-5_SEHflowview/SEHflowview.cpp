/*
SEHflowview.cpp
프로그램 설명 : EXCEPTION_EXECUTE_HANDLER의 예외처리 실행 흐름 파악
*/
#include <stdio.h>
#include <tchar.h>
#include <windows.h>

int _tmain(int argc, TCHAR* argv[]) {

	_tprintf(_T("start point! \n"));

	int* p = NULL;

	__try {
		*p = 100; // 널 포인터 역참조로 인해 Access Violation 예외 발생
		_tprintf(_T("value : %d"), *p);
	}
	// EXCEPTION_EXECUTE_HANDLER는 내부적으로 1을 반환
	__except (EXCEPTION_EXECUTE_HANDLER) {	// 예외가 발생했을 때 무조건 핸들러를 실행하라
		_tprintf(_T("exception occurred! \n"));
	}

	_tprintf(_T("end point! \n"));

	return 0;
}