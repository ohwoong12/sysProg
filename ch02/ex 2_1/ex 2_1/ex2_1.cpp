// MBCS1.cpp

#include<stdio.h>
#include<string.h>

int main(void) {
	char str[] = "ABC한글";	//ABC한글 이라는 문자열로 배열을 초기화
							//배열의 크기를 명시적으로 선언하지 않았으므로 문자열의 길이를 기반으로 크기가 결정
	int size = sizeof(str);	//배열의 크기 계산
	int len = strlen(str);	//배열의 길이 계산

	printf("배열의 크기: %d \n", size);
	printf("배열의 길이: %d \n", len);

	return 0;
}