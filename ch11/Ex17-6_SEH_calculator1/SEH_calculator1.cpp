#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <tchar.h>
#include <windows.h>

// ������ ��� ����
enum { DIV = 1, MUL, ADD, MIN, EXIT };

DWORD ShowMenu();	// �޴� ��� �Լ�
BOOL Calculator();	// ��� ó�� �� ���� ó��

int _tmain(int argc, TCHAR* argv[]) {
	BOOL state;

	do {
		state = Calculator();
	} while (state == TRUE);	// ����ڰ� ���Ḧ ������ ������ �ݺ�

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
	_gettc(stdin);  // ���๮�� ����

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
		* ���� if���̶� ��ħ
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
