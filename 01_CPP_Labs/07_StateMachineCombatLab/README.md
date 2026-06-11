# 07_StateMachineCombatLab

C++ enum class와 상태 머신을 사용해 간단한 전투 시스템을 구현한 과제입니다.

## Goals

- enum class 이해
- 상태 머신 기초 이해
- Character 상태 관리
- BattleSystem 클래스 설계
- unique_ptr 기반 객체 소유
- 상태에 따른 행동 제한 구현

## Features

- CharacterState: Idle, Attacking, Dead
- BattleResult: Hit, TargetDead, InvalidAttacker, InvalidTarget
- 캐릭터 추가
- 캐릭터 출력
- 공격
- 회복
- 죽은 캐릭터 행동 방지
- 생존 캐릭터 출력
- 전투 종료 판정

## Build

cl /std:c++20 /EHsc /W4 /utf-8 main.cpp CombatTypes.cpp Character.cpp BattleSystem.cpp /Fe:StateMachineCombatLab.exe

## Run
.\StateMachineCombatLab.exe

## Learned
enum class
switch with enum
state machine
state transition
BattleSystem
vector<unique_ptr<T>>
non-owning raw pointer

## Features

- CharacterState: Idle, Attacking, Hit, Dead
- BattleResult: Hit, TargetDead, InvalidAttacker, InvalidTarget
- 캐릭터 추가
- 캐릭터 출력
- 공격
- 회복
- 죽은 캐릭터 행동 방지
- 생존 캐릭터 출력
- 전투 종료 판정
- 20% 치명타
- 전투 턴 카운터
- 자동 전투 1턴
