#include <iostream>
#include <limits>
#include <memory>
#include <string>
#include <vector>

#include "Unit.h"

void PrintMenu();
void ClearInput();
int ReadInt(const std::string& prompt);
std::string ReadWord(const std::string& prompt);

int main()
{
    std::vector<std::unique_ptr<Unit>> party;

    party.push_back(CreateUnit("Knight", 120));
    party.push_back(CreateUnit("Archer", 80));
    party.push_back(CreateUnit("Mage", 60));

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

            Unit* target = FindUnitByName(party, name);

            if (target == nullptr)
            {
                std::cout << "Unit not found.\n";
            }
            else
            {
                target->TakeDamage(damage);
            }

            break;
        }

        case 3:
        {
            std::string name = ReadWord("Target name: ");
            int amount = ReadInt("Heal amount: ");

            Unit* target = FindUnitByName(party, name);

            if (target == nullptr)
            {
                std::cout << "Unit not found.\n";
            }
            else
            {
                target->Heal(amount);
            }

            break;
        }

        case 4:
        {
            std::string name = ReadWord("New unit name: ");
            int maxHp = ReadInt("Max HP: ");

            party.push_back(CreateUnit(name, maxHp));
            break;
        }

        case 5:
        {
            RunStackLifetimeDemo();
            break;
        }

        case 6:
        {
            RunUniquePtrDemo();
            break;
        }

        case 7:
        {
            RunSharedPtrDemo();
            break;
        }

        case 8:
        {
            RunWeakPtrDemo();
            break;
        }

        case 9:
        {
            RemoveDeadUnits(party);
            break;
        }

        case 0:
        {
            // 종료 시 도전 2 출력 용도.
            std::string name = ReadWord("Type name for challenge 2\n");
            ExtractUnitByName(party, name);

            std::cout << "Exit ownership lab.\n";
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
    std::cout << "=== Ownership Lab ===\n";
    std::cout << "1. Print party\n";
    std::cout << "2. Damage unit\n";
    std::cout << "3. Heal unit\n";
    std::cout << "4. Create unit\n";
    std::cout << "5. Run stack lifetime demo\n";
    std::cout << "6. Run unique_ptr demo\n";
    std::cout << "7. Run shared_ptr demo\n";
    std::cout << "8. Run weak_ptr demo\n";
    std::cout << "9. Remove dead units\n";
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
