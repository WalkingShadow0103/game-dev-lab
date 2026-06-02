# 03_InventorySystem

C++의 std::vector, struct, 참조, 반복문을 사용해 콘솔 인벤토리 시스템을 구현한 과제입니다.

## Features

- 아이템 추가
- 아이템 목록 출력
- 아이템 이름 검색
- 소비 아이템 사용
- 같은 이름의 아이템 추가 시 수량 증가
- 잘못된 수량과 가격 입력 방어

## 도전과제
1. 수량이 0이 되면 제거
2. 총 아이템 가치 출력
3. 아이템 타입 추가
4. 초기 아이템 3개 지급

## Learned

- std::vector
- struct
- index
- push_back
- empty
- size
- range/index based loop
- reference
- const reference
- function separation
- header/source split

## Build

cl /std:c++20 /EHsc /W4 /utf-8 main.cpp Inventory.cpp /Fe:InventorySystem.exe

## Run

./InventorySystem.exe

## Example Output

=== Inventory ===
0. Potion x3 | Price: 50 | Consumable: Yes
