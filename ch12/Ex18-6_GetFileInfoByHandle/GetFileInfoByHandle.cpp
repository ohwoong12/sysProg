#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <tchar.h>
#include <windows.h>
#include <locale.h>

#define STRING_LEN 100

void ShowAttributes(DWORD attrib);
void ShowFileTime(FILETIME t);

int _tmain(int argc, TCHAR* argv[])
{
	_tsetlocale(LC_ALL, _T("korean"));

	TCHAR fileName[] = _T("21018006_±Ç¿À¿õ_12ÁÖÂ÷.pdf");
	BY_HANDLE_FILE_INFORMATION fInfo;

	HANDLE hFile = CreateFile(fileName, GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	
	if (hFile == INVALID_HANDLE_VALUE) {
		_tprintf(_T("file open failed! \n"));
		return -1;
	}
	
	_tprintf(_T("File name : %s\n\n"), fileName);
	
	GetFileInformationByHandle(hFile, &fInfo);
	_tprintf(_T("File size : %d bytes\n\n"), fInfo.nFileSizeLow);
	_tprintf(_T("File created time : "));
	
	ShowFileTime(fInfo.ftCreationTime);
	_tprintf(_T("File last written time : "));
	
	ShowFileTime(fInfo.ftLastWriteTime);
	_tprintf(_T("File last accessed time : "));
	
	ShowFileTime(fInfo.ftLastAccessTime);
	_tprintf(_T("\nFile attributes : "));
	
	ShowAttributes(fInfo.dwFileAttributes);
	
	CloseHandle(hFile);
	return 0;
}

void ShowAttributes(DWORD attrib)
{
	// FILE_ATTRIBUTE_NORMAL
	if (attrib == FILE_ATTRIBUTE_NORMAL) {
		_tprintf(_T("Normal arributes \n"));
	}
	else {
		if (attrib & FILE_ATTRIBUTE_READONLY)
			_tprintf(_T("Read only \n"));
		if (attrib & FILE_ATTRIBUTE_HIDDEN)
			_tprintf(_T("Hidden \n"));
	}
	_tprintf(_T("\n"));
}

void ShowFileTime(FILETIME t)
{
	TCHAR fileTimeInfo[STRING_LEN];
	FILETIME ft = t;
	SYSTEMTIME stUTC, stLocal;

	FileTimeToSystemTime(&ft, &stUTC);
	SystemTimeToTzSpecificLocalTime(NULL, &stUTC, &stLocal);
	_stprintf(fileTimeInfo, _T("%02d/%02d/%02d %02d:%02d:%02d"),
		stLocal.wMonth, stLocal.wDay, stLocal.wYear,
		stLocal.wHour, stLocal.wMinute, stLocal.wSecond);
	_tprintf(_T("[%s]\n"), fileTimeInfo);
}