/*
SEH_calculator3.cpp
*/
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <tchar.h>
#include <windows.h>

enum { DIV = 1, MUL, ADD, MIN, EXIT };

DWORD ShowMenu();
BOOL Calculator();

void Divide(int, int);
void Multiple(int, int);
void Add(int, int);
void Min(int, int);

int _tmain(int argc, TCHAR* argv[]) {
	BOOL state;
	do {
		state = Calculator();
	} while (state == TRUE);
	return 0;
}

BOOL Calculator() {
	DWORD sel;
	int num1, num2, result;

	sel = ShowMenu();
	
	// 잘못된 메뉴 선택 시 즉시 예외 발생
	if (sel < DIV || sel > EXIT) {
		__try {
			RaiseException(EXCEPTION_ILLEGAL_INSTRUCTION, 0, 0, NULL);
		}
		__except (EXCEPTION_EXECUTE_HANDLER) {
			_tprintf(_T("Wrong menu selection! Try again!\n\n"));
		}
		return TRUE;  // 메뉴 다시 출력
	}

	if (sel == EXIT)
		return FALSE;
	
	_fputts(_T("Input Num1 Num2: "), stdout);
	_tscanf(_T("%d %d"), &num1, &num2);
	
	__try {
		__try {
			switch (sel) {
			case DIV:
				Divide(num1, num2);
				break;
			case MUL:
				Multiple(num1, num2);
				break;
			case ADD:
				Add(num1, num2);
				break;
			case MIN:
				Min(num1, num2);
				break;
			case EXIT:
				return TRUE;
			}
		}
		__finally {
			_tprintf(_T("End operation \n\n"));
		}
	}
	__except (EXCEPTION_EXECUTE_HANDLER) {
		_tprintf(_T("Wrong number inserted. Try again! \n\n"));
	}
	return TRUE;
}

DWORD ShowMenu() {
	DWORD sel;

	_fputts(_T("-----Menu----- \n"), stdout);
	_fputts(_T("num 1: Divide \n"), stdout);
	_fputts(_T("num 2: Multiple \n"), stdout);
	_fputts(_T("num 3: Add \n"), stdout);
	_fputts(_T("num 4: Min \n"), stdout);
	_fputts(_T("num 5: Exit \n"), stdout);
	_fputts(_T("Selection >> "), stdout);
	_tscanf(_T("%d"), &sel);
	_gettc(stdin);  // 개행문자 제거

	return sel;
}

void Divide(int a, int b) {
	_tprintf(_T("%d / %d = %d \n"), a, b, a / b);
}

void Multiple(int a, int b) {
	_tprintf(_T("%d * %d = %d \n"), a, b, a * b);
}

void Add(int a, int b) {
	_tprintf(_T("%d + %d = %d \n"), a, b, a + b);
}

void Min(int a, int b) {
	_tprintf(_T("%d - %d = %d \n"), a, b, a - b);
}