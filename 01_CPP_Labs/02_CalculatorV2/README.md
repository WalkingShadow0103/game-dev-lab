# 02_CalculatorV2

C++ 콘솔 입력, 함수 분리, switch 분기, 입력 검증을 연습하는 과제입니다.

## Features

- 사용자로부터 연산자 입력
- 사용자로부터 숫자 2개 입력
- 덧셈, 뺄셈, 곱셈, 나눗셈, 제곱
- 0으로 나누기 방지
- 잘못된 숫자 입력 처리
- q 입력 시 종료
- 피연산자에 p를 사용하면 이전 결과를 사용할 수 있음
- 성공한 연산 횟수 카운트

## Learned

- std::cin
- std::cin.fail()
- std::cin.clear()
- std::cin.ignore()
- switch
- while loop
- function declaration
- function definition
- header/source split

## Build

cl /std:c++20 /EHsc /W4 main.cpp Calculator.cpp /Fe:CalculatorV2.exe

## Run

.\CalculatorV2.exe

## Example Output

=== Calculator V2 ===
Operations: +, -, *, /, ^
Use p to reuse previous result.
Type q to quit.
Select operation:
Enter first number:
Enter second number: