#include<stdio.h>

int main() {
	char str[] = "�ѱ��Դϴ�";
	int i;

	for (i = 0; i < 5; i++)
		fputc(str[i], stdout);

	fputs("\n", stdout);

	for (i = 0; i < 10; i++)
		fputc(str[i], stdout);

	fputs("\n", stdout);

	return 0;
}