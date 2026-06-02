#include "Calculator.h"

int Add(int a, int b)
{
    return a + b;
}

int Subtract(int a, int b)
{
    return a - b;
}

int Multiply(int a, int b)
{
    return a * b;
}

float Divide(float a, float b)
{
    if (b == 0.0f)
    {
        return 0.0f;
    }

    return a / b;
}