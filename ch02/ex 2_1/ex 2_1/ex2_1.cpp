// MBCS1.cpp

#include<stdio.h>
#include<string.h>

int main(void) {
	char str[] = "ABC�ѱ�";	//ABC�ѱ� �̶�� ���ڿ��� �迭�� �ʱ�ȭ
							//�迭�� ũ�⸦ ��������� �������� �ʾ����Ƿ� ���ڿ��� ���̸� ������� ũ�Ⱑ ����
	int size = sizeof(str);	//�迭�� ũ�� ���
	int len = strlen(str);	//�迭�� ���� ���

	printf("�迭�� ũ��: %d \n", size);
	printf("�迭�� ����: %d \n", len);

	return 0;
}