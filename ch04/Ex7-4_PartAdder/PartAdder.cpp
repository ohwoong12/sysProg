/*
	PartAdder.cpp
	���α׷� ����: ���޵� ���� ������ �� ����
*/

#include<stdio.h>
#include<tchar.h>
#include<Windows.h>

int _tmain(int argc, TCHAR* argv[]) {
	if (argc != 3)	// ���ڰ� ����� ���޵��� ������ 1 ��ȯ
		return -1;

	//_tmain �Լ� ȣ�� ��(Command Line String�� ���ؼ�) ���޵Ǵ� �� ���� ���� ������ ��� ��
	// �θ� ���μ����� �ڽ� ���μ����� �����ϴ� �������� _tmain �Լ��� ���ڿ��� ������ �� ����
	DWORD start = _ttoi(argv[1]);	
	DWORD end = _ttoi(argv[2]);

	DWORD total = 0;

	for (DWORD i = start; i <= end; i++)
		total += i;

	return total;
}