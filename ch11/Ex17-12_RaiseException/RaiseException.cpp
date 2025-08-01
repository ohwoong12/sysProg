/*
RaiseException.cpp
프로그램 설명 : 소프트웨어 예외 생성 및 확인
*/
#include <stdio.h>
#include <tchar.h>
#include <windows.h>

void SoftwareException(void);

int _tmain(int argc, TCHAR* argv[]) {
	SoftwareException();

	_tprintf(_T("End of the _tmain \n"));
	return 0;
}void SoftwareException(void) {
	DWORD DefinedException = 0x00;
	
	// Severity
	DefinedException |= 0x01 << 31;
	DefinedException |= 0x01 << 30;

	// MS or Customer
	DefinedException |= 0x01 << 29;
	
	// Reserved, must be 0
	DefinedException |= 0x00 << 28;
	
	// Facility code
	DefinedException |= 0x000 << 16;
	
	// Exception code
	DefinedException |= 0x0008;

	__try {
		_tprintf(_T("Send : exception code : 0x%x \n"), DefinedException);
		RaiseException(DefinedException, 0, NULL, NULL);
	}
	__except (EXCEPTION_EXECUTE_HANDLER) {
		DWORD exptType = GetExceptionCode();
		_tprintf(_T("Recv: exception code : 0x%x \n"), exptType);
	}
}