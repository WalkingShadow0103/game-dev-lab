#include <iostream>
#include <limits>
#include <string>

#include "BattleSystem.h"
#include "CombatTypes.h"

void PrintMenu();
void ClearInput();
int ReadInt(const std::string& prompt);
std::string ReadWord(const std::string& prompt);

int main()
{
    BattleSystem battleSystem;

    battleSystem.AddCharacter("Knight", 120, 20);
    battleSystem.AddCharacter("Slime", 50, 8);
    battleSystem.AddCharacter("Goblin", 80, 12);

    bool isRunning = true;

    while (isRunning)
    {
        PrintMenu();

        int command = ReadInt("Select command: ");

        switch (command)
        {
        case 1:
        {
            battleSystem.PrintAllCharacters();
            break;
        }

        case 2:
        {
            std::string attackerName = ReadWord("Attacker name: ");
            std::string targetName = ReadWord("Target name: ");

            BattleResult result = battleSystem.Attack(attackerName, targetName);

            std::cout << "Battle result: " << ToString(result) << "\n";

            if (battleSystem.IsBattleOver())
            {
                std::cout << "Battle is over.\n";
            }

            break;
        }

        case 3:
        {
            std::string targetName = ReadWord("Target name: ");
            int amount = ReadInt("Heal amount: ");

            battleSystem.Heal(targetName, amount);
            break;
        }

        case 4:
        {
            std::string name = ReadWord("Character name: ");
            int maxHp = ReadInt("Max HP: ");
            int attackPower = ReadInt("Attack power: ");

            battleSystem.AddCharacter(name, maxHp, attackPower);
            break;
        }

        case 5:
        {
            battleSystem.PrintAliveCharacters();
            break;
        }

        case 6:
        {
            if (battleSystem.IsBattleOver())
            {
                std::cout << "Battle is over.\n";
            }
            else {
                Character* attacker = battleSystem.FindFirstAliveCharacter();
                Character* target = battleSystem.FindSecondAliveCharacter();

                BattleResult result = battleSystem.Attack(attacker->GetName(), target->GetName());

                std::cout << "Battle result: " << ToString(result) << "\n";
            }

            break;
        }

        case 0:
        {
            std::cout << "Exit state machine combat lab.\n";
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
    std::cout << "=== State Machine Combat Lab ===\n";
    std::cout << "1. Print all characters\n";
    std::cout << "2. Attack\n";
    std::cout << "3. Heal\n";
    std::cout << "4. Add character\n";
    std::cout << "5. Print alive characters\n";
    std::cout << "6. Auto battle one turn\n";
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
