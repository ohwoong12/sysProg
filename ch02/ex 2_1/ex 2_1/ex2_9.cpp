//#define UNICODE
//#define _UNICODE
/*
	��ũ�� UNICODE, _UNICODE�� ���Ǵ� ������� ���� ������ �����ؾ���
	���ǵ� ��ũ�ο� ���� ������Ͽ� ����� �ڷ����� ���°� �����Ǳ� �����̴�.
	���� ������� ���� ���Ŀ� �����ϰ� �Ǹ�, �ƹ��� ���� �غ��� ��������.
*/

//#undef UNICODE
//#undef _UNICODE
//���� undef�� ���� ���̰� 8�� ��.

#include<stdio.h>
#include<tchar.h>
#include<Windows.h>

int wmain(void) {
	TCHAR str[] = _T("1234567");
	/*
		��ũ�ΰ� ���ǵǾ����� TCHAR -> wchar_t, _T("1234567") -> L"1234567"�� �ν�
		��ũ�� UNICODE, _UNICODE ���Ǵ� ������� ���� ������ �����ؾ� ��
	*/
	int size = sizeof(str);

	printf("string.length: %d \n", size);

	return 0;
}