#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

//�ڽ� ���μ���
int _tmain(int argc, TCHAR* argv[]) {
	DWORD val1, val2;
	val1 = _ttoi(argv[1]);	// _ttoi �Լ��� ���ڿ� �����͸� ������ �����ͷ� �����Ű�� atoi �Լ���, �����ڵ� ����� _wtoi�� ���� �����ϱ� ���� ��ũ��
	val2 = _ttoi(argv[2]);

	_tprintf(_T("%d + %d = %d \n"), val1, val2, val1 + val2);

	_gettchar();	// ���α׷��� ������ ��� ���߱� ����, getchar �Լ��� �����ڵ� ����� getwchar �Լ��� ���� �����ϱ� ���� ��ũ�� �Լ�
	// ���α׷��� �帧�� �Ͻ� ������Ű�� ���� ����.

	return 0;
}