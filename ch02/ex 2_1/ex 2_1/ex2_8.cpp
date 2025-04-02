#include<stdio.h>
#include<Windows.h>

/*
windows.h 파일은 windows 기반 프로그래밍을 하는데에 있어 기본적으로 항상 포함해야 하는 헤더 파일.
windows.h는 windows 프로그래밍에 필요한 다양한 종류의 헤더파일을 포함하고 있음
CHAR, WCHAR은 winnt.h에 정의되어 있고, windef.h가 winnt.h를, windows.h가 windef.h를 포함하고 있음.
LPSTR = char*
*/

int wmain(int argc, wchar_t* argv[]) {
	LPSTR str1 = "SBCS Style String 1";
	LPWSTR str2 = L"WBCS Style String 2";

}