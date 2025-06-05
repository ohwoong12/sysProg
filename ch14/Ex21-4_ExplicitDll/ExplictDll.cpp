/*
ExplicitDll.cpp
Explicit DLL 활용
*/
#include <stdio.h>
#include <tchar.h>
#include <windows.h>

typedef void (*SWAP_FUNC) (int*, int*);

int _tmain(int argc, TCHAR* argv[])
{
	HMODULE hintLib;
	SWAP_FUNC SwapFunction;

	hintLib = LoadLibrary(_T("SwapDll"));                      // SwapDll.dll을 laod (가상 주소 공간에 맵핑)
	if (hintLib == NULL) {
		_tprintf(_T("LoadLibrary failed! \n"));
		return -1;
	}

	SwapFunction = (SWAP_FUNC)GetProcAddress(hintLib, "swap"); // DLL내에서 찾고자 하는 함수가 swap
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

