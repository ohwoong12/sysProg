#include<stdio.h>
#include<Windows.h>

/*
windows.h ������ windows ��� ���α׷����� �ϴµ��� �־� �⺻������ �׻� �����ؾ� �ϴ� ��� ����.
windows.h�� windows ���α׷��ֿ� �ʿ��� �پ��� ������ ��������� �����ϰ� ����
CHAR, WCHAR�� winnt.h�� ���ǵǾ� �ְ�, windef.h�� winnt.h��, windows.h�� windef.h�� �����ϰ� ����.
LPSTR = char*
*/

int wmain(int argc, wchar_t* argv[]) {
	LPSTR str1 = "SBCS Style String 1";
	LPWSTR str2 = L"WBCS Style String 2";

}