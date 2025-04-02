#include<stdio.h>
#include<string.h>


/*  
	windows 2000 이상의 운영체제는 내부적으로 모든 문자열을 유니코드 기반으로 처리.
	따라서 MBCS 기반 문자열을 처리하는 함수를 처리할 때, 운영체제로 전달되는 문자열을 내부적으로 2바이트 유니코드 형식으로 바꾸기 때문에
	프로그램 성능이 낮아질 수 있다.

	wchar__t형 변수는 2byte 메모리 공간이 할당됨, 따라서 유니코드를 기반으로 문자를 표현하는 것이 가능
*/

int main(void) {
	wchar_t str[] = L"ABC";	//wchar_t를 사용했기 때문에 영어도 2byte, NULL도 2byte로 처리됨
	int size = sizeof(str);	//sizeof는 함수가 아닌 연산자이기 때문에 변화 없음	
	int len = wcslen(str);	//strlen은 SBCS 기반 문자열을 처리하기 위한 함수이기에 WBCS 기반 함수로 변경하여 사용

	printf("배열의 크기: %d \n", size);
	printf("문자열 길이: %d \n", len);

	return 0;
}