#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <tchar.h>
#include <windows.h>

// 열거형 상수 선언
enum { DIV = 1, MUL, ADD, MIN, EXIT };

DWORD ShowMenu();	// 메뉴 출력 함수
BOOL Calculator();	// 계산 처리 및 예외 처리

int _tmain(int argc, TCHAR* argv[]) {
	BOOL state;

	do {
		state = Calculator();
	} while (state == TRUE);	// 사용자가 종료를 선택할 때까지 반복

	return 0;
}

DWORD ShowMenu() {
	DWORD sel;

	_fputts(_T("-----Menu----- \n"), stdout);
	_fputts(_T("num 1: Divide \n"), stdout);
	_fputts(_T("num 2: Multiple \n"), stdout);
	_fputts(_T("num 3: Add \n"), stdout);
	_fputts(_T("num 4: Min \n"), stdout);
	_fputts(_T("num 5: Exit \n"), stdout);
	_fputts(_T("Selection (key in a number) >> "), stdout);
	_tscanf(_T("%d"), &sel);
	_gettc(stdin);  // 개행문자 제거

	return sel;
}

BOOL Calculator() {
	DWORD sel;
	int num1, num2, result;

	sel = ShowMenu();

	if (sel == EXIT)
		return FALSE;

	_fputts(_T("Input Num1 Num2: "), stdout);
	_tscanf(_T("%d %d"), &num1, &num2);

	__try {
		switch (sel) {
		case DIV:
			result = num1 / num2;
			_tprintf(_T(" %d / %d = %d \n\n"), num1, num2, result);
			break;
		case MUL:
			result = num1 * num2;
			_tprintf(_T(" %d * %d = %d \n\n"), num1, num2, result);
			break;
		case ADD:
			result = num1 + num2;
			_tprintf(_T(" %d + %d = %d \n\n"), num1, num2, result);
			break;
		case MIN:
			result = num1 - num2;
			_tprintf(_T(" %d - %d = %d \n\n"), num1, num2, result);
			break;
		/*
		* 위에 if문이랑 겹침
		case EXIT:
			return FALSE;
		*/
		default:
			_tprintf(_T("invalid selection. \n"));
			return true;
		}
	}
	__except (EXCEPTION_EXECUTE_HANDLER) {
		_tprintf(_T("Wrong number inserted. Try again! \n\n"));
	}
	return TRUE;
}
