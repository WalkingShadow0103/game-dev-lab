#include "Inventory.h"

#include <iostream>

Item::Item()
    : name("")
    , quantity(0)
    , price(0)
    , isConsumable(false)
    , type("Unknown")
{
}

Item::Item(
    const std::string& itemName,
    int itemQuantity,
    int itemPrice,
    bool consumable,
    const std::string& itemType
)
    : name(itemName)
    , quantity(itemQuantity)
    , price(itemPrice)
    , isConsumable(consumable)
    , type(itemType)
{
}

Inventory::Inventory()
    : m_items()
    , m_maxSlots(20)
{
}

Inventory::Inventory(int maxSlots)
    : m_items()
    , m_maxSlots(maxSlots)
{
    if (m_maxSlots <= 0)
    {
        m_maxSlots = 20;
    }
}

bool Inventory::AddItem(
    const std::string& name,
    int quantity,
    int price,
    bool isConsumable,
    const std::string& type
)
{
    if (name.empty())
    {
        std::cout << "Item name cannot be empty.\n";
        return false;
    }

    if (quantity <= 0)
    {
        std::cout << "Quantity must be greater than 0.\n";
        return false;
	}

    if (price < 0)
    {
        std::cout << "Price cannot be negative.\n";
        return false;
	}

	int index = FindItemIndexByName(name);

    if (index >= 0)
    {
        m_items[static_cast<std::size_t>(index)].quantity += quantity;
        std::cout << "Stacked item: " << name << "\n";
		return true;
    }

    if(!HasFreeSlot())
    {
        std::cout << "Inventory is full.\n";
        return false;
	}

    Item newItem(name, quantity, price, isConsumable, type);
    m_items.push_back(newItem);

    std::cout << "Added item: " << name << "\n";
    return true;
}

bool Inventory::UseItem(const std::string& name)
{
    int index = FindItemIndexByName(name);

    if (index < 0)
    {
        std::cout << "Item not found: " << name << "\n";
        return false;
	}

	Item& item = m_items[static_cast<std::size_t>(index)];

    if (!item.isConsumable)
    {
        std::cout << "Item is not consumable: " << name << "\n";
		return false;
	}

    if (item.quantity <= 0)
    {
        std::cout << "Item quantity is zero: " << item.name << "\n";
        return false;
    }

	item.quantity -= 1;
    std::cout << "Used item: " << name << "\n";

    if (item.quantity == 0)
    {
		auto erasePosition = m_items.begin() + static_cast<std::ptrdiff_t>(index);
        m_items.erase(erasePosition);
		std::cout << "Removed empty item: " << name << "\n";
    }

    return true;

}

void Inventory::Print() const
{
    std::cout << "=== Inventory ===\n";
    std::cout << "Slots: " << m_items.size() << " / " << m_maxSlots << "\n";

    if (m_items.empty())
    {
        std::cout << "Inventory is empty.\n";
        return;
    }

    for (std::size_t i = 0; i < m_items.size(); ++i)
    {
        PrintItem(m_items[i], i);
    }
}

bool Inventory::PrintItemByName(const std::string& name) const
{
	int index = FindItemIndexByName(name);

    if (index < 0)
    {
        std::cout << "Item not found.\n";
        return false;
    }

	PrintItem(m_items[static_cast<std::size_t>(index)], static_cast<std::size_t>(index));

    return true;
}

void Inventory::PrintTotalValue() const
{
    int totalValue = 0;

    for (const Item& item : m_items)
    {
        totalValue += item.quantity * item.price;
    }

    std::cout << "Total value: " << totalValue << "\n";
}

std::size_t Inventory::GetItemCount() const
{
    return m_items.size();
}

int Inventory::GetMaxSlots() const
{
    return m_maxSlots;
}

int Inventory::FindItemIndexByName(const std::string& name) const
{

    for (std::size_t i = 0; i < m_items.size(); ++i)
    {
        if (m_items[i].name == name)
        {
            return static_cast<int>(i);
        }
	}

    return -1;
}

bool Inventory::HasFreeSlot() const
{
    return m_items.size() < static_cast<std::size_t>(m_maxSlots);
}

void Inventory::PrintItem(const Item& item, std::size_t index) const
{
    std::cout << index << ". "
        << item.name
        << " x" << item.quantity
        << " | Type: " << item.type
        << " | Price: " << item.price
        << " | Consumable: " << (item.isConsumable ? "Yes" : "No")
        << "\n";
}

// 도전과제 1. RemoveItem 구현
    // quantity <= 0 이면 실패, 메시지 출력
    // 아이템이 없으면 실패, 메시지 출력
    // 제거 수량 < 보유 수량이면 수량만 감소
    // 제거 수량 >= 보유 수량이면 아이템 자체 삭제
    // 성공 true 반환
    // 실패 false 반환
bool Inventory::RemoveItem(const std::string& name, int quantity)
{
    if (quantity <= 0)
    {
        std::cout << "Quantity to remove must be greater than 0.\n";
        return false;
    }

    int index = FindItemIndexByName(name);

    if (index < 0)
    {
        std::cout << "Item not found: " << name << "\n";
        return false;
    }

    Item& item = m_items[static_cast<std::size_t>(index)];

    if (quantity < item.quantity)
    {
        item.quantity -= quantity;
        std::cout << "Removed " << quantity << " of " << name << ". Remaining: " << item.quantity << "\n";
        return true;
    }
    else
    {
        auto erasePosition = m_items.begin() + static_cast<std::ptrdiff_t>(index);
        m_items.erase(erasePosition);
        std::cout << "Removed all of " << name << ".\n";
        return true;
    }
}

// 도전과제 2. 타입별 출력
// 같은 타입 아이템 있으면 해당 타입 아이템만 출력
// 같은 타입 아이템 없으면 'No items of type: <type>' 출력
// 비교 방식은 대소문자 구분
void Inventory::PrintItemsByType(const std::string& type) const
{
	int matchCount = 0;
    for (std::size_t i = 0; i < m_items.size(); ++i)
    {
        if (m_items[i].type == type)
        {
            PrintItem(m_items[i], i);
			matchCount++;
        }
	}
    if (matchCount == 0)
    {
        std::cout << "No items of type: " << type << "\n";
	}
}

// 도전과제 3. 가장 비싼 아이템 출력
// price 단가가 가장 높은 아이템
// 인벤토리가 비어있으면 'Inventory is empty.' 출력 후 false
// 아이템 있으면 price가 가장 높은 아이템 출력 후 true
// price가 같은 아이템이 있으면 먼저 발견한 아이템 출력.
bool Inventory::PrintMostExpensiveItem() const
{
    if (m_items.empty())
    {
        std::cout << "Inventory is empty.\n";
        return false;
    }

    std::size_t mostExpensiveIndex = 0;

    for (std::size_t i = 1; i < m_items.size(); ++i)
    {
        if (m_items[i].price > m_items[mostExpensiveIndex].price)
        {
            mostExpensiveIndex = i;
        }
    }

    std::cout << "Most expensive item:\n";
    PrintItem(m_items[mostExpensiveIndex], mostExpensiveIndex);
    return true;
}
