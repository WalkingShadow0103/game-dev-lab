#include <iostream>
#include <limits>
#include <string>

#include "Calculator.h"

void PrintMenu();
void ClearInput();
float ReadNumber(std::string prompt);
char ReadOperator();

// 도전 2. 이전 결과 저장 기능 추가
float previousResult = 0.0f;

// 도전 3. 연산 횟수 카운터 추가
int counter = 0;

int main()
{
    bool isRunning = true;

    while (isRunning)
    {
        PrintMenu();

        char operation = ReadOperator();

        if (operation == 'q' || operation == 'Q')
        {
            std::cout << "Exit calculator.\n";
            isRunning = false;
            continue;
        }

        float firstNumber = ReadNumber("Enter first number: ");
        float secondNumber = ReadNumber("Enter second number: ");

        float result = 0.0f;
        bool isValidOperation = true;

        switch (operation)
        {
        case '+':
            result = Add(firstNumber, secondNumber);
            break;

        case '-':
            result = Subtract(firstNumber, secondNumber);
            break;

        case '*':
            result = Multiply(firstNumber, secondNumber);
            break;

        case '/':
            if (!CanDivide(secondNumber))
            {
                std::cout << "Cannot divide by zero.\n";
                isValidOperation = false;
            }
            else
            {
                result = Divide(firstNumber, secondNumber);
            }
            break;

			// 도전 1. 제곱 연산 추가, exponent 정수 판별 처리
        case '^':
            if (secondNumber != floor(secondNumber))
            {
                std::cout << "Invalid exponent. Must be an integer.\n";
                isValidOperation = false;
            }
            else
            {
                result = Power(firstNumber, exponent);
            }
            break;

        default:
            std::cout << "Invalid operation.\n";
            isValidOperation = false;
            break;
        }

        if (isValidOperation)
        {
            std::cout << "Result: " << result << "\n";
			// 도전 2. 이전 결과 저장 기능 추가
			previousResult = result;
        }

        std::cout << "\n";

		// 도전 3. 연산 횟수 카운터 추가
        counter++;
    }

    return 0;
}

void PrintMenu()
{
    std::cout << "=== Calculator V2 ===\n";
    std::cout << "Operations: +, -, *, /\n";
    std::cout << "Type q to quit.\n";
}

void ClearInput()
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

float ReadNumber(std::string prompt)
{
    float value = 0.0f;

    while (true)
    {
        std::cout << prompt;
        std::cin >> value;

        if (std::cin.fail())
        {
            std::cout << "Invalid number. Try again.\n";
            ClearInput();
            continue;
        }

        ClearInput();
        return value;
    }
}

char ReadOperator()
{
    char operation = '\0';

    std::cout << "Select operation: ";
    std::cin >> operation;

    ClearInput();

    return operation;
}