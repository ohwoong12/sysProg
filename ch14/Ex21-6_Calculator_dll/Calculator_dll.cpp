/*
 calculator_dll.cpp
 DLL ���ۿ�
*/

#include "pch.h"
#define _COMPILING_DLL_CALCULATOR
#include "Calculator.h"

LIBSPEC int Add(int a, int b)
{
	return a + b;
}
LIBSPEC int Min(int a, int b)
{
	return a - b;
}
LIBSPEC double Div(double a, double b)
{
	return a / b;
}
LIBSPEC double Mul(double a, double b)
{
	return a * b;
}