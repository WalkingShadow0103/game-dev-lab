#include "Calculator.h"

float Add(float a, float b)
{
	return a + b;
}

float Subtract(float a, float b)
{
	return a - b;
}

float Multiply(float a, float b)
{
	return a * b;
}

bool CanDivide(float b)
{
	return b != 0.0f;
}

float Divide(float a, float b)
{
	if (!CanDivide(b))
	{
		return 0.0f;
	}
	
	return a / b;
}

// 도전 1. 제곱 연산 추가
float Power(float base, int exponenet)
{
	float result = 1.0f;
	for (int i = 0; i < exponenet; ++i)
	{
		result *= base;
	}
	return result;
}