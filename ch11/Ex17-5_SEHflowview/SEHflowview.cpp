/*
SEHflowview.cpp
���α׷� ���� : EXCEPTION_EXECUTE_HANDLER�� ����ó�� ���� �帧 �ľ�
*/
#include <stdio.h>
#include <tchar.h>
#include <windows.h>

int _tmain(int argc, TCHAR* argv[]) {

	_tprintf(_T("start point! \n"));

	int* p = NULL;

	__try {
		*p = 100; // �� ������ �������� ���� Access Violation ���� �߻�
		_tprintf(_T("value : %d"), *p);
	}
	// EXCEPTION_EXECUTE_HANDLER�� ���������� 1�� ��ȯ
	__except (EXCEPTION_EXECUTE_HANDLER) {	// ���ܰ� �߻����� �� ������ �ڵ鷯�� �����϶�
		_tprintf(_T("exception occurred! \n"));
	}

	_tprintf(_T("end point! \n"));

	return 0;
}