#include<stdio.h>
#include<Windows.h>
#include<tchar.h>

int _tmain(void) {
	HANDLE hFile = CreateFile(_T("AABC.DAT"),GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
	// ABC.DAT �̸��� ������ �����Ϸ� ������ �������� �����Ƿ� ������ �߻��ϰ� 10��° �ٷ� �̵�
	// OPEN_EXISTING: �����ϴ� ������ ���ڴٴ� �ɼ�

	if (hFile == INVALID_HANDLE_VALUE) {	//CreateFile �Լ��� �������� �ʴ� ���� ABC.DAT�� ������ �ϸ�, INVALID_HANDLE_VALUE�� ��ȯ ��
		_tprintf(_T("error code: %d \n"), GetLastError());
		return 0;
	}

	return 0;
}

// ���� �ڵ�2(ERROR_FLIE_NOT_FOUND)�� �ý����� ������ ������ ã�� �� ������ �ǹ���
// ���� Ȯ���� ������ �߻��� ���Ŀ� �ٷ� �ؾ���
// ������ �߻��ϸ�, �ٷ� �̾ GetLastError �Լ��� ȣ���ؼ� ������ ���� ��