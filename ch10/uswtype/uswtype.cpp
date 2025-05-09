#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <tchar.h> // _tfpoen()
#include <windows.h>

void TypeC(TCHAR* filename);

int _tmain(int argc, TCHAR* argv[])
{
	if (argc < 2) {
		_fputts(_T("Usage: type xxxx.txt \n"), stdout);
		return -1;
	}
	TypeC(argv[1]);
	return 0;
}

void TypeC(TCHAR* filename)
{
	int c;
	FILE* pFile = _tfopen(filename, _T("rt")); // 텍스트 모드로 file read
	if (pFile == NULL) {
		_tprintf(_T("Error in opening file"));
		return;
	}
	while (1) {
		c = _fgettc(pFile);
		if (feof(pFile)) {
			break;
		}
		_tprintf(_T("%c"), c);
	}
	fclose(pFile);
}
