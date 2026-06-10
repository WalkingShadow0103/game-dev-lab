# 06_OwnershipLab

C++의 객체 수명, RAII, unique_ptr, shared_ptr, weak_ptr를 연습하는 과제입니다.

## Goals

- 객체 생성과 소멸 시점 이해
- stack 객체 수명 이해
- RAII 개념 이해
- unique_ptr 소유권 이해
- std::move를 통한 소유권 이전 이해
- shared_ptr 참조 카운트 이해
- weak_ptr 관찰자 패턴 이해

## Features

- Unit class
- constructor/destructor log
- vector<unique_ptr<Unit>> party
- damage/heal
- create unit
- stack lifetime demo
- unique_ptr demo
- shared_ptr demo
- weak_ptr demo

## Build

cl /std:c++20 /EHsc /W4 /utf-8 main.cpp Unit.cpp /Fe:OwnershipLab.exe

## Run

.\OwnershipLab.exe

## Learned

RAII
destructor
unique_ptr
make_unique
std::move
shared_ptr
make_shared
use_count
weak_ptr
lock
expired
non-owning pointer

## Q&A

Q1. shared_ptr를 서로 물고 있으면 왜 객체가 안 지워질 수 있는가?
A1. 소유자에게서 객체를 지운다고 해도 다른 소유자가 있기 때문에.

Q2. weak_ptr는 이 문제를 어떻게 줄이는가?
A2. 소유하지 않기에 지워지는 건 보장됨.
