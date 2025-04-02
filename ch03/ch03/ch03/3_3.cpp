#include<stdio.h>
#include<Windows.h>
#include<tchar.h>

int _tmain(void) {
	HANDLE hFile = CreateFile(_T("AABC.DAT"),GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
	// ABC.DAT 이름의 파일을 개방하려 하지만 존재하지 않으므로 오류가 발생하고 10번째 줄로 이동
	// OPEN_EXISTING: 존재하는 파일을 열겠다는 옵션

	if (hFile == INVALID_HANDLE_VALUE) {	//CreateFile 함수가 존재하지 않는 파일 ABC.DAT을 열고자 하면, INVALID_HANDLE_VALUE가 반환 됨
		_tprintf(_T("error code: %d \n"), GetLastError());
		return 0;
	}

	return 0;
}

// 에러 코드2(ERROR_FLIE_NOT_FOUND)는 시스템이 지정된 파일을 찾을 수 없음을 의미함
// 오류 확인은 오류가 발생한 직후에 바로 해야함
// 오류가 발생하면, 바로 이어서 GetLastError 함수를 호출해서 오류를 얻어야 함