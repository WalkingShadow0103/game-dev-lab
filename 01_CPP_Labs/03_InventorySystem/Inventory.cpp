#include "Inventory.h"

#include <iostream>

void PrintInventory(const std::vector<Item>& inventory)
{
    std::cout << "=== Inventory ===\n";

    if (inventory.empty())
    {
        std::cout << "Inventory is empty.\n";
        return;
    }

    for (std::size_t i = 0; i < inventory.size(); ++i)
    {
        const Item& item = inventory[i];

        std::cout << i << ". "
            << item.name
            << " x" << item.quantity
            << " | Price: " << item.price
            << " | Consumable: " << item.isConsumable
            << "\n";
    }
}

void AddItem(
    std::vector<Item>& inventory,
    const std::string& name,
    int quantity,
    int price,
    bool isConsumable,
    const std::string& type
)
{
    int itemIndex = FindItemIndexByName(inventory, name);
    if (itemIndex != -1)
    {
        inventory[itemIndex].quantity += quantity;
    }
    else
    {
        Item newItem;
        newItem.name = name;
        newItem.quantity = quantity;
        newItem.price = price;
        newItem.isConsumable = isConsumable;
		newItem.type = type;
        inventory.push_back(newItem);
	}
}

int FindItemIndexByName(
    const std::vector<Item>& inventory,
    const std::string& name
)
{
    for (std::size_t i = 0; i < inventory.size(); ++i)
    {
        if (inventory[i].name == name)
        {
            return static_cast<int>(i);
        }
	}

    return -1;
}

bool UseItem(
    std::vector<Item>& inventory,
    const std::string& name
)
{
	int itemIndex = FindItemIndexByName(inventory, name);
    if (itemIndex == -1)
    {
        std::cout << "Item not found: " << name << "\n";
		return false;
    }
    // 방어 코드: 소비 아이템이 아닌 아이템 사용 방지
    else if (!inventory[itemIndex].isConsumable)
    {
        std::cout << "Item is not consumable: " << name << "\n";
		return false;
    }
    // 방어 코드: 없는 아이템 사용 방지
    else if (inventory[itemIndex].quantity <= 0)
    {
        std::cout << "No more items left: " << name << "\n";
        return false;
    }
    else
    {
        inventory[itemIndex].quantity -= 1;
        std::cout << "Used item: " << name << "\n";
        // 도전 과제 1. 수량이 0이 되면 제거.
        if (inventory[itemIndex].quantity == 0)
        {
            inventory.erase(inventory.begin() + itemIndex);
		}
        return true;
	}
}

// 도전 과제 2. 총 아이템 가치 출력
void PrintTotalValue(const std::vector<Item>& inventory)
{
    int totalValue = 0;
    for (const Item& item : inventory)
    {
		std::cout << item.name << " x" << item.quantity << ",  price " << item.price << " -> " << item.quantity * item.price << "\n";
        totalValue += item.quantity * item.price;
    }
    std::cout << "Total value: " << totalValue << "\n";
}
