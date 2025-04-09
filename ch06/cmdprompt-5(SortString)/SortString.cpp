#define _CRT_SECURE_NO_WARNINGS

#define MAX_STRING_NUM 100
#define MAX_STRING_LEN 256

#include<stdio.h>
#include<tchar.h>
#include<Windows.h>

void SortString(void) {
	TCHAR stringArr[MAX_STRING_NUM][MAX_STRING_LEN];
	DWORD nStr;

	for (nStr = 0; nStr < MAX_STRING_NUM; nStr++) {
		TCHAR* isEOF = _fgetts(stringArr[nStr], MAX_STRING_LEN, stdin);
		if (isEOF == NULL) // Ctrl+Z 입력시 isEOF에 NULL 반환 됨
			break;
	}
	TCHAR strTemp[MAX_STRING_LEN];
	for (UINT i = 0; i < nStr; i++) {
		for (UINT j = nStr - 1; j > i; j--) {
			if (_tcscmp(stringArr[j - 1], stringArr[j]) > 0) {
				_tcscpy(strTemp, stringArr[j - 1]);
				_tcscpy(stringArr[j - 1], stringArr[j]);
				_tcscpy(stringArr[j], strTemp);
			}
		}
	}
	for (UINT i = 0; i < nStr; i++) {
		_fputts(stringArr[i], stdout);
	}
}
int _tmain(int argc, TCHAR* argv[])
{
	SortString();
	return 0;
}