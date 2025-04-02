//PolymorphicType1.cpp
//Ex 3_1

#include<stdio.h>
#include<Windows.h>
#include<tchar.h>

// UINT_PTR�� Polymorphic �ڷ������� windows.h�� ���Ǻη� ���ǵǾ� ����
// ������Ʈ�� �Ӽ��� ���� �ڵ����� 64��Ʈ, 32��Ʈ�� ���Ǹ� ������ ���Ǻ� �ڵ�� �ʿ� ����
UINT_PTR CalDistance(UINT_PTR a, UINT_PTR b) {
	if (a >= b) return a - b;
	else return b - a;
}

int _tmain(void) {
	INT32 val1 = 10;	//INT = int, UINT = unsigned int
	INT32 val2 = 20;	//INT32 = signed 32bit integer

	_tprintf(_T("Position %011x \n"), (UINT_PTR)&val1, (UINT_PTR)&val2);
	// CalDistance �Լ��� �� ������ �ּҰ��� ���ڷ� ���޹޾Ƽ� �� ���� ��, �� �޸𸮻��� �Ÿ��� ����ؼ� ��ȯ�� �ִ� �Լ�
	// ���� �޸��� �Ÿ��� ����ϱ� ���ؼ� �����Ͱ� ���ϴ� �ּҰ��� ���������� ��ȯ�ؼ� �����ϰ� �ִ�.	
	_tprintf(_T("Distance : %011u bytes \n"), CalDistance((UINT_PTR)&val1, (UINT_PTR)&val2));

	return 0;
}