#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <cmath>

#include "Calculator.h"

void PrintMenu(bool hasPreviousResult, float previousResult);
void ClearInput();
float ReadOperand(std::string prompt, bool hasPreviousResult, float previousResult);
char ReadOperator();

int main()
{
    // 도전 2. 이전 결과 저장 기능 추가
    bool hasPR = false;
    float PR = 0.0f;

    // 도전 3. 연산 횟수 카운터 추가
    int counter = 0;

    bool isRunning = true;

    while (isRunning)
    {
        PrintMenu(hasPR, PR);

        char operation = ReadOperator();

        if (operation == 'q' || operation == 'Q')
        {
            std::cout << "Exit calculator.\n";
            isRunning = false;
            continue;
        }

        if (operation != '+' && operation != '-' && operation != '*' && operation != '/' && operation != '^')
        {
            std::cout << "Invalid operation. Try again.\n";
            isRunning = false;
            continue;
		}

        float firstNumber = ReadOperand("Enter first number: ", hasPR, PR);
        float secondNumber = ReadOperand("Enter second number: ", hasPR, PR);

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
            else if (secondNumber < 0)
            {
                std::cout << "Negative exponent not supported.\n";
                isValidOperation = false;
            }
			else
            {
                result = Power(firstNumber, static_cast<int>(secondNumber));
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
			hasPR = true;
            PR = result;
            counter++;
        }

        std::cout << "\n";

		// 도전 3. 연산 횟수 카운터 추가
		std::cout << "Count: " << counter << "\n";
    }

    return 0;
}

void PrintMenu(bool hasPR, float PR)
{
    std::cout << "=== Calculator V2 ===\n";
    std::cout << "Operations: +, -, *, /, ^\n";
    if (hasPR) {
        std::cout << "previous result p = " << PR << ".\n";
    }
    else {
        std::cout << "Use p to reuse previous result.\n";
    }
    std::cout << "Type q to quit.\n";
}

void ClearInput()
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

float ReadOperand(std::string prompt, bool hasPreviousResult, float previousResult)
{
    while (true)
    {
        std::cout << prompt;

        std::string input;
        std::cin >> input;

        if (input == "p" || input == "P")
        {
            if (hasPreviousResult)
            {
                return previousResult;
            }

            std::cout << "No previous result yet. Enter a number.\n";
            continue;
        }

        std::istringstream stream(input);
        float value = 0.0f;
        char leftover = '\0';

        if (stream >> value && !(stream >> leftover))
        {
            return value;
        }

        std::cout << "Invalid number. Try again.\n";
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