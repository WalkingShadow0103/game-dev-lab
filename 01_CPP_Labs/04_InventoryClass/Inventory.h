#pragma once

#include <cstddef>
#include <string>
#include <vector>

struct Item
{
    std::string name;
    int quantity;
    int price;
    bool isConsumable;
    std::string type;

    Item();
    Item(
        const std::string& itemName,
        int itemQuantity,
        int itemPrice,
        bool consumable,
        const std::string& itemType
    );
};

class Inventory
{
public:
    Inventory();
    Inventory(int maxSlots);

    bool AddItem(
        const std::string& name,
        int quantity,
        int price,
        bool isConsumable,
        const std::string& type
    );

    bool UseItem(const std::string& name);

    void Print() const;
    bool PrintItemByName(const std::string& name) const;
    void PrintTotalValue() const;

    std::size_t GetItemCount() const;
    int GetMaxSlots() const;
    // 도전과제 1. RemoveItem 구현
    // quantity <= 0 이면 실패, 메시지 출력
    // 아이템이 없으면 실패, 메시지 출력
    // 제거 수량 < 보유 수량이면 수량만 감소
    // 제거 수량 >= 보유 수량이면 아이템 자체 삭제
    // 성공 true 반환
    // 실패 false 반환
    bool RemoveItem(const std::string& name, int quantity);
    // 도전과제 2. 타입별 출력
    // 같은 타입 아이템 있으면 해당 타입 아이템만 출력
    // 같은 타입 아이템 없으면 'No items of type: <type>' 출력
    // 비교 방식은 대소문자 구분
    void PrintItemsByType(const std::string& type) const;
    // 도전과제 3. 가장 비싼 아이템 출력
    // price 단가가 가장 높은 아이템
    // 인벤토리가 비어있으면 'Inventory is empty.' 출력 후 false
    // 아이템 있으면 price가 가장 높은 아이템 출력 후 true
    // price가 같은 아이템이 있으면 먼저 발견한 아이템 출력.
    bool PrintMostExpensiveItem() const;

private:
    int FindItemIndexByName(const std::string& name) const;
    bool HasFreeSlot() const;
    void PrintItem(const Item& item, std::size_t index) const;

private:
    std::vector<Item> m_items;
    int m_maxSlots;
};
