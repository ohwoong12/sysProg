#include<stdio.h>
#include<string.h>
//#include<locale.h>

/*
	Windows 2000 �̻��� �ü���� �⺻������ �����ڵ带 ���� (���������� ��� ���ڿ��� �����ڵ� ������� ó��)
	printf()�� �����ڵ� ������ wprintf()
	wprintf(), fputws() ���� �Լ����� ���ؼ� �����ڵ� ������� �ѱ��� ����ϰ� �ʹٸ�
	(_wsetlocale (LC_ALL, L"korean"); , #include<locale.h> �� �ۼ�
	_wsetlocale�� ���α׷��� ����Ǵ� ���� �� ������ ���� ������ �����ϴ� �� ���Ǵ� �Լ�
*/

int main(void) {
	wchar_t str[] = L"ABC";
	int size = sizeof(str);
	int len = wcslen(str);

	//_wsetlocale(LC_ALL, L"korean");
	wprintf(L"�迭�� ũ��: %d \n", size);
	wprintf(L"Array Length: %d \n", len);

	return 0;
}