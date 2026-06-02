#include <iostream>
#include <limits>
#include <string>
#include <vector>

#include "Inventory.h"

void PrintMenu();
void ClearInput();
int ReadInt(const std::string& prompt);
std::string ReadWord(const std::string& prompt);
bool ReadBoolAsYesNo(const std::string& prompt);

int main()
{
    std::vector<Item> inventory;
	// 도전 과제 4. 인벤토리 초기 아이템 추가
    AddItem(inventory, "Potion", 3, 50, true, "Consumable");
    AddItem(inventory, "Sword", 1, 300, false, "Weapon");
    AddItem(inventory, "Bomb", 2, 100, true, "Consumable");

    bool isRunning = true;

    while (isRunning)
    {
        PrintMenu();

        int command = ReadInt("Select command: ");

        switch (command)
        {
        case 1:
        {
            PrintInventory(inventory);
            break;
        }

        case 2:
        {
            std::string name = ReadWord("Item name: ");
            int quantity = ReadInt("Quantity: ");
            // 방어 코드: 수량 0 이하 방지
            while (quantity <= 0)
            {
                std::cout << "Quantity must be greater than 0. Try again.\n";
				quantity = ReadInt("Quantity: ");
            }
            int price = ReadInt("Price: ");
            // 방어 코드: 가격 음수 방지
            while (price < 0)
            {
				std::cout << "Price cannot be negative. Try again.\n";
				price = ReadInt("Price: ");
            }
            bool isConsumable = ReadBoolAsYesNo("Consumable? (y/n): ");
			// 도전 과제 3. 아이템 타입 추가 (예: "Weapon", "Armor", "Consumable")
			std::string type = ReadWord("Item type (Weapon/Armor/Consumable): ");

            AddItem(inventory, name, quantity, price, isConsumable, type);
            break;
        }

        case 3:
        {
            std::string name = ReadWord("Use item name: ");
            UseItem(inventory, name);
            break;
        }

        case 4:
        {
            std::string name = ReadWord("Find item name: ");
            int index = FindItemIndexByName(inventory, name);

            if (index >= 0)
            {
                std::cout << "Found at index: " << index << "\n";
            }
            else
            {
                std::cout << "Item not found.\n";
            }

            break;
        }
        // 도전 과제 2. 총 아이템 가치 출력
        case 5:
        {
			PrintTotalValue(inventory);
            break;
        }

        case 0:
        {
            std::cout << "Exit inventory.\n";
            isRunning = false;
            break;
        }

        default:
        {
            std::cout << "Invalid command.\n";
            break;
        }
        }

        std::cout << "\n";
    }

    return 0;
}

void PrintMenu()
{
    std::cout << "=== Inventory System ===\n";
    std::cout << "1. Print inventory\n";
    std::cout << "2. Add item\n";
    std::cout << "3. Use item\n";
    std::cout << "4. Find item\n";
	// 도전 과제 2. 총 아이템 가치 출력
	std::cout << "5. Print total value\n";
    std::cout << "0. Quit\n";
}

void ClearInput()
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int ReadInt(const std::string& prompt)
{
    int value = 0;

    while (true)
    {
        std::cout << prompt;
        std::cin >> value;

        if (std::cin.fail())
        {
            std::cout << "Invalid number. Try again.\n";
            ClearInput();
            continue;
        }

        ClearInput();
        return value;
    }
}

std::string ReadWord(const std::string& prompt)
{
    std::string value;

    std::cout << prompt;
    std::cin >> value;
    ClearInput();

    return value;
}

bool ReadBoolAsYesNo(const std::string& prompt)
{
    while (true)
    {
        std::string input = ReadWord(prompt);

        if (input == "y" || input == "Y")
        {
            return true;
        }

        if (input == "n" || input == "N")
        {
            return false;
        }

        std::cout << "Please enter y or n.\n";
    }
}
