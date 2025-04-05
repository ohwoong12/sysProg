/*
	PartAdder.cpp
	프로그램 설명: 전달된 인자 사이의 수 덧셈
*/

#include<stdio.h>
#include<tchar.h>
#include<Windows.h>

int _tmain(int argc, TCHAR* argv[]) {
	if (argc != 3)	// 인자가 제대로 전달되지 않으면 1 반환
		return -1;

	//_tmain 함수 호출 시(Command Line String을 통해서) 전달되는 두 개의 숫자 정보를 얻는 것
	// 부모 프로세스는 자식 프로세스를 생성하는 과정에서 _tmain 함수에 문자열을 전달할 수 있음
	DWORD start = _ttoi(argv[1]);	
	DWORD end = _ttoi(argv[2]);

	DWORD total = 0;

	for (DWORD i = start; i <= end; i++)
		total += i;

	return total;
}