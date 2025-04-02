//PolymorphicType1.cpp
//Ex 3_1

#include<stdio.h>
#include<Windows.h>
#include<tchar.h>

// UINT_PTR은 Polymorphic 자료형으로 windows.h에 조건부로 정의되어 있음
// 프로젝트의 속성에 따라 자동으로 64비트, 32비트로 사용되며 별도의 조건부 코드는 필요 없음
UINT_PTR CalDistance(UINT_PTR a, UINT_PTR b) {
	if (a >= b) return a - b;
	else return b - a;
}

int _tmain(void) {
	INT32 val1 = 10;	//INT = int, UINT = unsigned int
	INT32 val2 = 20;	//INT32 = signed 32bit integer

	_tprintf(_T("Position %011x \n"), (UINT_PTR)&val1, (UINT_PTR)&val2);
	// CalDistance 함수는 두 변수의 주소값을 인자로 전달받아서 그 값의 차, 즉 메모리상의 거리를 계산해서 반환해 주는 함수
	// 순수 메모리의 거리를 계산하기 위해서 포인터가 지니는 주소값을 정수형으로 변환해서 전달하고 있다.	
	_tprintf(_T("Distance : %011u bytes \n"), CalDistance((UINT_PTR)&val1, (UINT_PTR)&val2));

	return 0;
}