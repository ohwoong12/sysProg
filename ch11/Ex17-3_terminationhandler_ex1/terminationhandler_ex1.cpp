/*
terminationhandlerex1.cpp
*/
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <tchar.h>
#include <windows.h>

/* ���ڿ��� �Է¹ް� ���Ͽ� �����ϴ� �Լ� **/
int ReadStringAndWrite(void);

int _tmain(int argc, TCHAR* argv[]) {
	int state = 0;	// ���� �ڵ带 �����ϴ� ����

	// ���� ������ ���� �ݺ������� ���ڿ��� �Է� ����
	while (1) {
		state = ReadStringAndWrite();

		// �Լ� ���� �� ���� �߻��ϸ� ����Ǵ� �κ�
		if (state == -1) {
			_tprintf(_T("Some problem occurred in function!\n"));
			ReadStringAndWrite();	// ���� �߻� �� �ѹ� �� �õ�
			break;
		}
		// �Էµ� ���ڿ� ���̰� 0�� ��� ����
		if (state == 0) {
			_tprintf(_T("Graceful exit!\n"));
			break;
		}
	}
	return 0;
}

// ���ڿ��� �Է¹޾� ���Ͽ� �����ϴ� �Լ�
int ReadStringAndWrite(void) {
	FILE* pFile = NULL;			// ���� ������
	TCHAR* strBuffer = NULL;	// ���ڿ��� ������ ������

	// ���� ó�� ��� (�ڿ� ������ ���� ���)
	__try {
		pFile = _tfopen(_T("string.txt"), _T("a+t"));	// string.txt ������ �ؽ�Ʈ append ���� ���� (������ �ڵ� ����)
		if (pFile == NULL)
			return -1;	// ���� ���� ���� �� ���� ��ȯ

		DWORD strLen = 0;	// �Է��� ���ڿ��� ����

		_tprintf(_T("Input string length (0 to exit) : "));
		_tscanf(_T("%d"), &strLen);	// ���ڿ� ���� �Է� �ޱ�

		_gettc(stdin); // scanf �� ���� ����(\n) ����

		if (strLen == 0)
			return 0; // ���� ����, �׷��� file�� memory�� �����ؾ� ��

		// �Էµ� ���� ��ŭ �޸� ���� �Ҵ� (+1�� NULL���� ����)	
		strBuffer = (TCHAR*)malloc((strLen + 1) * sizeof(TCHAR));
		if (strBuffer == NULL)
			return -1;

		_tprintf(_T("\nInput string : "));
		_tscanf(_T("%[^\n]"), strBuffer); // ����('\n') ������ ���ڿ� �Է� �ޱ�

		_ftprintf(pFile, _T("%s\n"), strBuffer); // �Էµ� ���ڿ��� ���Ͽ� �����ϰ� �ٹٲ� �߰� 
	}
	// ���� �߻� ���ο� �����ϰ� �ڿ� ����
	__finally {
		// ������ ���� ������ �ݱ�
		if (!pFile == NULL)
			fclose(pFile);
		// �޸� ����
		if (!strBuffer == NULL)
			free(strBuffer);
	}
		return 0;
}