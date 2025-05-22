/*
FileTimeInformation.cpp
���α׷� ���� : ���� �ð� ���� Ȯ���ϴ� ����
*/
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <tchar.h>
#include <windows.h>

#define STRING_LEN 100

int _tmain(int argc, TCHAR* argv[])
{
	TCHAR fileName[] = _T("���� ������Ʈ.txt");
	TCHAR fileCreateTimeInfo[STRING_LEN];
	TCHAR fileAccessTimeInfo[STRING_LEN];
	TCHAR fileWriteTimeInfo[STRING_LEN];

	FILETIME ftCreate, ftAccess, ftWrite;

	SYSTEMTIME stCreateUTC, stCreateLocal;
	SYSTEMTIME stAccessUTC, stAccessLocal;
	SYSTEMTIME stWriteUTC, stWriteLocal;

	HANDLE hFile = CreateFile(fileName, GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

	if (hFile == INVALID_HANDLE_VALUE) {
		_tprintf(_T("File open failed! \n"));
		return -1;
	}

	// ������ �ð� ���� ����
	if (!GetFileTime(hFile, &ftCreate, &ftAccess, &ftWrite)) {
		_tprintf(_T("GetFileTime error !\n"));
		return -1;
	}	// �ð� ���� ��ȯ
	FileTimeToSystemTime(&ftCreate, &stCreateUTC);
	SystemTimeToTzSpecificLocalTime(NULL, &stCreateUTC, &stCreateLocal);

	FileTimeToSystemTime(&ftAccess, &stAccessUTC);
	SystemTimeToTzSpecificLocalTime(NULL, &stAccessUTC, &stAccessLocal);

	FileTimeToSystemTime(&ftWrite, &stWriteUTC);
	SystemTimeToTzSpecificLocalTime(NULL, &stWriteUTC, &stWriteLocal);

	_stprintf(fileCreateTimeInfo, _T("%02d/%02d/%02d %02d:%02d:%02d"),
		stCreateLocal.wMonth, stCreateLocal.wDay, stCreateLocal.wYear,
		stCreateLocal.wHour, stCreateLocal.wMinute,
		stCreateLocal.wSecond);
	_stprintf(fileAccessTimeInfo, _T("%02d/%02d/%02d %02d:%02d:%02d"),
		stAccessLocal.wMonth, stAccessLocal.wDay, stAccessLocal.wYear,
		stAccessLocal.wHour, stAccessLocal.wMinute,
		stAccessLocal.wSecond);
	_stprintf(fileWriteTimeInfo, _T("%02d/%02d/%02d %02d:%02d:%02d"),
		stWriteLocal.wMonth, stWriteLocal.wDay, stWriteLocal.wYear,
		stWriteLocal.wHour, stWriteLocal.wMinute, stWriteLocal.wSecond);

	_tprintf(_T("File created time : %s \n"), fileCreateTimeInfo);
	_tprintf(_T("File accessed time : %s \n"), fileAccessTimeInfo);
	_tprintf(_T("File written time : %s \n"), fileWriteTimeInfo);

	CloseHandle(hFile);
	return 0;
}