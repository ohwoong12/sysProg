/*
ExplicitDll.cpp
Explicit DLL Ȱ��
*/
#include <stdio.h>
#include <tchar.h>
#include <windows.h>

typedef void (*SWAP_FUNC) (int*, int*);

int _tmain(int argc, TCHAR* argv[])
{
	HMODULE hintLib;
	SWAP_FUNC SwapFunction;

	hintLib = LoadLibrary(_T("SwapDll"));                      // SwapDll.dll�� laod (���� �ּ� ������ ����)
	if (hintLib == NULL) {
		_tprintf(_T("LoadLibrary failed! \n"));
		return -1;
	}

	SwapFunction = (SWAP_FUNC)GetProcAddress(hintLib, "swap"); // DLL������ ã���� �ϴ� �Լ��� swap
		if (SwapFunction == NULL) {
			_tprintf(_T("GetProcAddress failed! \n"));
			return -1;
		}

	_tprintf(_T("This is an explicit linking test \n"));

	int a = 100;
	int b = 200;

	_tprintf(_T("Before : %d %d \n"), a, b);
	SwapFunction(&a, &b);
	_tprintf(_T("After : %d %d\n"), a, b);

	BOOL isSuccess = FreeLibrary(hintLib);
	if (isSuccess == NULL) {
		_tprintf(_T("FreeLibrary failed! \n"));
		return -1;

	}
	return 1;
}

