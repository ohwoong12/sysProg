#include<stdio.h>
#include<string.h>
#include "locale.h"

int main(void) {
	wchar_t str[] = L"ABC한글";	//wchar_t는 유니코드 기반의 2바이트 크기 문자 값을 저장할 변수를 선언할 때 사용하는 자료형
	int size = sizeof(str);
	int len = wcslen(str);

	_wsetlocale(LC_ALL, L"Korean");
	wprintf(L"배열의 크기: %d \n",size);
	wprintf(L"문자열 길이: %d \n", len);

	return 0;
}

/*	
	유니코드로 한글을 호출하려면 출력함수(wprintf, fputsw 등) 호출 전에
	프로그램이 실행되는 나라 및 지역에 대한 정보를 설정하는
	_wsetlocale 함수가 먼저 호출되어야 한다
*/

/*
Locale 범주 (특정 특성을 지역에 맞출 수 있음)
• LC_ALL: 모든 특성을 지정 국가의 언어 형식으로 설정
• LC_CTYPE: 문자 집합, 대소문자 구분 여부, 문자 분류 등을 지정
• LC_COLLATE: 문자열 비교 순서를 지정
• LC_MONETARY: 통화 단위, 소수점 기호 등을 지정
• LC_NUMERIC: 숫자 형식, 소수점 표기법 등을 지정
• LC_TIME: 날짜 및 시간 형식을 지정
• LC_MESSAGES: 시스템 메시지 및 오류 메시지의 언어를 지정
*/