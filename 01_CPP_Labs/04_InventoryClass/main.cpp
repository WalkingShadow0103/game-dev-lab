#include <iostream>
#include <limits>
#include <string>

#include "Inventory.h"

void PrintMenu();
void ClearInput();
int ReadInt(const std::string& prompt);
std::string ReadWord(const std::string& prompt);
bool ReadBoolAsYesNo(const std::string& prompt);

int main()
{
    Inventory inventory(10);

    inventory.AddItem("Potion", 3, 50, true, "Consumable");
    inventory.AddItem("Sword", 1, 300, false, "Weapon");
    inventory.AddItem("Bomb", 2, 100, true, "Consumable");

    bool isRunning = true;

    while (isRunning)
    {
        PrintMenu();

        int command = ReadInt("Select command: ");

        switch (command)
        {
        case 1:
        {
            inventory.Print();
            break;
        }

        case 2:
        {
            std::string name = ReadWord("Item name: ");
            int quantity = ReadInt("Quantity: ");
            int price = ReadInt("Price: ");
            bool isConsumable = ReadBoolAsYesNo("Consumable? (y/n): ");
            std::string type = ReadWord("Item type (Weapon/Armor/Consumable): ");

            inventory.AddItem(name, quantity, price, isConsumable, type);
            break;
        }

        case 3:
        {
            std::string name = ReadWord("Use item name: ");
            inventory.UseItem(name);
            break;
        }

        case 4:
        {
            std::string name = ReadWord("Find item name: ");
            inventory.PrintItemByName(name);
            break;
        }

        case 5:
        {
            inventory.PrintTotalValue();
            break;
        }
		// 도전과제 1. Remove item 메뉴
		case 6:
        {
            std::string name = ReadWord("Remove item name: ");
            int quantity = ReadInt("Quantity to remove: ");
            inventory.RemoveItem(name, quantity);
            break;
		}
		// 도전과제 2. Print items by type 메뉴
        case 7:
        {
            std::string type = ReadWord("Item type to print: ");
            inventory.PrintItemsByType(type);
		    break;
		}
        // 도전과제 3. Print most expensive item 메뉴
        case 8:
        {
			inventory.PrintMostExpensiveItem();
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
    std::cout << "=== Inventory Class ===\n";
    std::cout << "1. Print inventory\n";
    std::cout << "2. Add item\n";
    std::cout << "3. Use item\n";
    std::cout << "4. Find item\n";
    std::cout << "5. Print total value\n";
	// 도전과제 1. Remove item 메뉴 추가
	std::cout << "6. Remove item\n";
	// 도전과제 2. Print items by type 메뉴 추가
	std::cout << "7. Print items by type\n";
	// 도전과제 3. Print most expensive item 메뉴 추가
	std::cout << "8. Print most expensive item\n";
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
