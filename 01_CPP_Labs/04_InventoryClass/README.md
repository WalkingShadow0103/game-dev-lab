# 04_InventoryClass

Day 3의 인벤토리 시스템을 class 기반으로 리팩토링한 과제입니다.

## Goals

- struct와 class의 차이 이해
- public/private 접근 제어 이해
- 생성자 사용
- 멤버 함수 구현
- const 멤버 함수 사용
- vector를 private 멤버 변수로 숨기기

## Features

- Inventory class
- Item struct
- 최대 슬롯 수 설정
- 아이템 추가
- 같은 이름 아이템 수량 증가
- 아이템 사용
- 수량 0 아이템 제거
- 아이템 검색
- 총 가치 출력
- 내부 vector 캡슐화

## Build

cl /std:c++20 /EHsc /W4 /utf-8 main.cpp Inventory.cpp /Fe:InventoryClass.exe

## Run

.\InventoryClass.exe

## Example Output

=== Inventory ===
Slots: 3 / 10
0. Potion x3 | Type: Consumable | Price: 50 | Consumable: Yes
1. Sword x1 | Type: Weapon | Price: 300 | Consumable: No
2. Bomb x2 | Type: Consumable | Price: 100 | Consumable: Yes
