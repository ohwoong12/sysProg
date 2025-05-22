#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <tchar.h>
#include <windows.h>
#include <locale.h>

int _tmain(int argc, TCHAR* argv[])
{
	_tsetlocale(LC_ALL, _T("korean"));

	TCHAR fileName[MAX_PATH];
	TCHAR bufFilePath[MAX_PATH];
	TCHAR filePart[MAX_PATH];
	LPTSTR lpFilePart;
	DWORD result;

	lpFilePart = filePart;
	
	_tprintf(_T("Insert file name to find : "));
	//_tscanf(_T("%s"), fileName);
	_fgetts(fileName, MAX_PATH, stdin);

	// ���� ���� ����
	TCHAR* newline = _tcschr(fileName, _T('\n'));	// 	���ڿ� fileName���� \n ���ڸ� ã��
	if (newline) *newline = _T('\0');	// newline�� NULL�� �ƴ��� �˻�, ���� ���ڸ� �� ���� ���ڷ� �����Ͽ� ���ڿ� �� ����

	//result = SearchPath(NULL, fileName, NULL, MAX_PATH, bufFilePath, &lpFilePart);	
	// ����ȭ�� ��� ����
	TCHAR desktopPath[MAX_PATH] = _T("C:\\Users\\oungt\\Desktop");
	result = SearchPath(desktopPath, fileName, NULL, MAX_PATH, bufFilePath, &lpFilePart);


	if (result == 0) {
		_tprintf(_T("File not found! \n"));
	}
	else {
		_tprintf(_T("File path : %s \n"), bufFilePath);
		_tprintf(_T("File name : %s \n"), lpFilePart);
	}
	return 0;
}