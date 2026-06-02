#pragma once

#include <string>
#include <vector>

struct Item
{
    std::string name;
    int quantity;
    int price;
    bool isConsumable;
	// 도전 과제 3. 아이템 타입 추가 (예: "Weapon", "Armor", "Consumable")
    std::string type;
};

void PrintInventory(const std::vector<Item>& inventory);

void AddItem(
    std::vector<Item>& inventory,
    const std::string& name,
    int quantity,
    int price,
    bool isConsumable,
    // 도전 과제 3. 아이템 타입 추가 (예: "Weapon", "Armor", "Consumable")
    const std::string& type
);

int FindItemIndexByName(
    const std::vector<Item>& inventory,
    const std::string& name
);

bool UseItem(
    std::vector<Item>& inventory,
    const std::string& name
);

// 도전 과제 2. 총 아이템 가치 출력
void PrintTotalValue(
    const std::vector<Item>& inventory
);
