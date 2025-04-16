/*
PartAdder.cpp
프로그램 설명 : 전달된 인자(두 수) 사이의 모든 수를 덧셈
*/
#include <stdio.h>
#include <tchar.h>
#include <windows.h>

int _tmain(int argc, TCHAR* argv[]) {
	if (argc != 3) {
		return -1;
	}

	int start = _ttoi(argv[1]);
	int end = _ttoi(argv[2]);
	int total = 0;

	for (int i = start; i <= end; i++) {
		total += i;
	}

	_tprintf(_T("Part sum : % d \n"), total);

	return total;
}