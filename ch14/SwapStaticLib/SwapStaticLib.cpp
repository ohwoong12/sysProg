﻿// SwapStaticLib.cpp : 정적 라이브러리를 위한 함수를 정의합니다.
//

#include "pch.h"
#include "framework.h"

void swap(int* v1, int* v2) // swap 함수 정의
{
	int temp = *v1;
	*v1 = *v2;
	*v2 = temp;
}