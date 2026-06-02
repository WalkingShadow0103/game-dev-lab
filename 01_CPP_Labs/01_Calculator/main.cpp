#include <iostream>
#include "Calculator.h"

int main()
{
    int a = 10;
    int b = 5;

    std::cout << "=== Calculator ===\n";
    std::cout << "Add: " << Add(a, b) << "\n";
    std::cout << "Subtract: " << Subtract(a, b) << "\n";
    std::cout << "Multiply: " << Multiply(a, b) << "\n";
    std::cout << "Divide: " << Divide(static_cast<float>(a), static_cast<float>(b)) << "\n";

    return 0;
}