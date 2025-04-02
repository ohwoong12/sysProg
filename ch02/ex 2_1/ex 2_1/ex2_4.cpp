#include<stdio.h>
#include<string.h>
//#include<locale.h>

/*
	Windows 2000 이상의 운영체제는 기본적으로 유니코드를 지원 (내부적으로 모든 문자열을 유니코드 기반으로 처리)
	printf()의 유니코드 버전은 wprintf()
	wprintf(), fputws() 같은 함수들을 통해서 유니코드 기반으로 한글을 출력하고 싶다면
	(_wsetlocale (LC_ALL, L"korean"); , #include<locale.h> 을 작성
	_wsetlocale은 프로그램이 실행되는 나라 및 지역에 대한 정보를 설정하느 데 사용되는 함수
*/

int main(void) {
	wchar_t str[] = L"ABC";
	int size = sizeof(str);
	int len = wcslen(str);

	//_wsetlocale(LC_ALL, L"korean");
	wprintf(L"배열의 크기: %d \n", size);
	wprintf(L"Array Length: %d \n", len);

	return 0;
}