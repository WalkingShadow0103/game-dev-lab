#include <iostream>
#include <limits>
#include <string>
#include <vector>

#include "Character.h"

void PrintMenu();
void ClearInput();
int ReadInt(const std::string& prompt);
std::string ReadWord(const std::string& prompt);
void RunVectorPointerInvalidationDemo();

int main()
{
    std::vector<Character> party;

    party.push_back(Character("Knight", 120, 15));
    party.push_back(Character("Archer", 80, 20));
    party.push_back(Character("Mage", 60, 30));

    bool isRunning = true;

    while (isRunning)
    {
        PrintMenu();

        int command = ReadInt("Select command: ");

        switch (command)
        {
        case 1:
        {
            PrintParty(party);
            break;
        }

        case 2:
        {
            std::string name = ReadWord("Target name: ");
            int damage = ReadInt("Damage: ");

            Character* target = FindCharacterByName(party, name);
            DamageByPointer(target, damage);
            break;
        }

        case 3:
        {
            std::string name = ReadWord("Target name: ");
            int amount = ReadInt("Heal amount: ");

            Character* target = FindCharacterByName(party, name);
            HealByPointer(target, amount);
            break;
        }

        case 4:
        {
            RunPassingDemo();
            break;
        }

        case 5:
        {
            std::string name = ReadWord("Target name: ");

            Character* target = FindCharacterByName(party, name);

            if (target == nullptr)
            {
                std::cout << "Character not found.\n";
            }
            else
            {
                PrintAddressDemo(*target);
            }

            break;
        }

        case 0:
        {
            std::cout << "Exit pointer lab.\n";
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

    // 도전 3 실험용.
    RunVectorPointerInvalidationDemo();

    return 0;
}

void PrintMenu()
{
    std::cout << "=== Pointer Reference Lab ===\n";
    std::cout << "1. Print party\n";
    std::cout << "2. Damage character by pointer\n";
    std::cout << "3. Heal character by pointer\n";
    std::cout << "4. Run value/reference/pointer demo\n";
    std::cout << "5. Print address demo\n";
    std::cout << "6. Print lowest HP character\n";
    std::cout << "7. Revive character\n";
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

void RunVectorPointerInvalidationDemo()
{
    std::vector<Character> characters;
    characters.push_back(Character("A", 100, 10));

    Character* savedPointer = &characters[0];

    std::cout << "Before push_back: " << savedPointer << "\n";

    characters.push_back(Character("B", 100, 10));
    characters.push_back(Character("C", 100, 10));
    characters.push_back(Character("D", 100, 10));

    std::cout << "After push_back, first element address: " << &characters[0] << "\n";
    std::cout << "Saved pointer: " << savedPointer << "\n";
}
