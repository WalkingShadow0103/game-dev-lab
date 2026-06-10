# 05_PointerReferenceLab

C++의 값 전달, 참조 전달, 포인터 전달, 주소 연산자, nullptr 처리를 연습하는 과제입니다.

## Goals

- 값 전달과 원본 수정 여부 이해
- 참조 전달 이해
- 포인터 전달 이해
- 주소 연산자 `&` 이해
- 역참조와 `->` 이해
- `nullptr` 방어 코드 작성
- vector 원소를 포인터로 찾고 즉시 사용하는 패턴 연습

## Features

- 캐릭터 파티 출력
- 이름으로 캐릭터 검색
- 포인터로 데미지 적용
- 포인터로 회복 적용
- 값/참조/포인터 전달 차이 데모
- 주소 출력 데모
- nullptr 방어

## Build

cl /std:c++20 /EHsc /W4 /utf-8 main.cpp Character.cpp /Fe:PointerReferenceLab.exe

## Run

.\PointerReferenceLab.exe

## Learned

pass by value
pass by reference
pass by pointer
address-of operator
nullptr
-> operator
stack object basics
vector element pointer caution
