//#define UNICODE
//#define _UNICODE
/*
	매크로 UNICODE, _UNICODE의 정의는 헤더파일 선언 이전에 등장해야함
	정의된 매크로에 따라서 헤더파일에 선언된 자료형의 형태가 결정되기 때문이다.
	만약 헤더파일 선언 이후에 등장하게 되면, 아무리 정의 해봤자 무용지물.
*/

//#undef UNICODE
//#undef _UNICODE
//위에 undef를 쓰면 길이가 8이 됨.

#include<stdio.h>
#include<tchar.h>
#include<Windows.h>

int wmain(void) {
	TCHAR str[] = _T("1234567");
	/*
		매크로가 정의되었으니 TCHAR -> wchar_t, _T("1234567") -> L"1234567"로 인식
		매크로 UNICODE, _UNICODE 정의는 헤더파일 선언 이전에 등장해야 함
	*/
	int size = sizeof(str);

	printf("string.length: %d \n", size);

	return 0;
}