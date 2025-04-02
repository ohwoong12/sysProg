#include<Windows.h>
#include<tchar.h>

int _tmain(void) {
	HANDLE hFile = CreateFile(_T("ABC2.DAT"), GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_NEW , FILE_ATTRIBUTE_NORMAL, NULL);
	_tprintf(_T("error cod : %d \n"), GetLastError());	// Error code 0은 파일 열기 성공을 의미

	hFile = CreateFile(_T("ABC2.DAT"), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	_tprintf(_T("error code : %d \n"), GetLastError());
	// Error code 32는 The process cannot access the file because it is being used by another process”의미

	return 0;
}