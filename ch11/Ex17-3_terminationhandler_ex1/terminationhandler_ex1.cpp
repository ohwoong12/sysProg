/*
terminationhandlerex1.cpp
*/
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <tchar.h>
#include <windows.h>

/* 문자열을 입력받고 파일에 저장하는 함수 **/
int ReadStringAndWrite(void);

int _tmain(int argc, TCHAR* argv[]) {
	int state = 0;	// 상태 코드를 저장하는 변수

	// 무한 루프를 통해 반복적으로 문자열을 입력 받음
	while (1) {
		state = ReadStringAndWrite();

		// 함수 실행 시 오류 발생하면 실행되는 부분
		if (state == -1) {
			_tprintf(_T("Some problem occurred in function!\n"));
			ReadStringAndWrite();	// 문제 발생 후 한번 더 시도
			break;
		}
		// 입력된 문자열 길이가 0인 경우 종료
		if (state == 0) {
			_tprintf(_T("Graceful exit!\n"));
			break;
		}
	}
	return 0;
}

// 문자열을 입력받아 파일에 저장하는 함수
int ReadStringAndWrite(void) {
	FILE* pFile = NULL;			// 파일 포인터
	TCHAR* strBuffer = NULL;	// 문자열을 저장할 포인터

	// 예외 처리 블록 (자원 해제를 위해 사용)
	__try {
		pFile = _tfopen(_T("string.txt"), _T("a+t"));	// string.txt 파일을 텍스트 append 모드로 열기 (없으면 자동 생성)
		if (pFile == NULL)
			return -1;	// 파일 열기 실패 시 오류 반환

		DWORD strLen = 0;	// 입력할 문자열의 길이

		_tprintf(_T("Input string length (0 to exit) : "));
		_tscanf(_T("%d"), &strLen);	// 문자열 길이 입력 받기

		_gettc(stdin); // scanf 후 남은 개행(\n) 제거

		if (strLen == 0)
			return 0; // 정상 종료, 그래도 file과 memory는 해제해야 함

		// 입력된 길이 만큼 메모리 동적 할당 (+1은 NULL문자 포함)	
		strBuffer = (TCHAR*)malloc((strLen + 1) * sizeof(TCHAR));
		if (strBuffer == NULL)
			return -1;

		_tprintf(_T("\nInput string : "));
		_tscanf(_T("%[^\n]"), strBuffer); // 엔터('\n') 전까지 문자열 입력 받기

		_ftprintf(pFile, _T("%s\n"), strBuffer); // 입력된 문자열을 파일에 저장하고 줄바꿈 추가 
	}
	// 예외 발생 여부와 무관하게 자원 해제
	__finally {
		// 파일이 열려 있으면 닫기
		if (!pFile == NULL)
			fclose(pFile);
		// 메모리 해제
		if (!strBuffer == NULL)
			free(strBuffer);
	}
		return 0;
}