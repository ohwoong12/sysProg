#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

//자식 프로세스
int _tmain(int argc, TCHAR* argv[]) {
	DWORD val1, val2;
	val1 = _ttoi(argv[1]);	// _ttoi 함수는 문자열 데이터를 정수형 데이터로 변경시키는 atoi 함수와, 유니코드 기반의 _wtoi를 동시 지원하기 위한 매크로
	val2 = _ttoi(argv[2]);

	_tprintf(_T("%d + %d = %d \n"), val1, val2, val1 + val2);

	_gettchar();	// 프로그램의 실행을 잠시 멈추기 위해, getchar 함수와 유니코드 기반의 getwchar 함수를 동시 지원하기 위한 매크로 함수
	// 프로그램의 흐름을 일시 정지시키기 위해 삽입.

	return 0;
}