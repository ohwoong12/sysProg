#include <stdio.h>
#include <tchar.h>
#include <windows.h>

void ShowAttributes(DWORD attrib);

int _tmain(int argc, TCHAR* argv[]) {
	_tprintf(_T("Original file attributes \n"));

	DWORD attrib = GetFileAttributes(_T("모프 프로젝트.txt"));
	ShowAttributes(attrib);
	attrib |= (FILE_ATTRIBUTE_READONLY | FILE_ATTRIBUTE_HIDDEN);
	
	SetFileAttributes(_T("모프 프로젝트.txt"), attrib);
	_tprintf(_T("Changed file attributes \n"));
	attrib = GetFileAttributes(_T("모프 프로젝트.txt"));
	
	ShowAttributes(attrib);

	return 0;
}

void ShowAttributes(DWORD attrib) {
	// FILE_ATTRIBUTE_NORMAL
	if (attrib == FILE_ATTRIBUTE_NORMAL) {
		_tprintf(_T("Normal arributes \n"));
	}
	else {
		if (attrib & FILE_ATTRIBUTE_READONLY) // & : bit-wise and
			_tprintf(_T("Read only \n"));
		if (attrib & FILE_ATTRIBUTE_HIDDEN)
			_tprintf(_T("Hidden \n"));
	}
	_tprintf(_T("attrib : %0xh \n\n"), attrib);
}