#pragma once

#include <memory>
#include <string>
#include <vector>
#include <random>

#include "Character.h"
#include "CombatTypes.h"

class BattleSystem
{
public:
    BattleSystem();

    void AddCharacter(const std::string& name, int maxHp, int attackPower);

    Character* FindCharacterByName(const std::string& name);
    const Character* FindCharacterByName(const std::string& name) const;

    BattleResult Attack(const std::string& attackerName, const std::string& targetName);
    bool Heal(const std::string& targetName, int amount);

    void PrintAllCharacters() const;
    void PrintAliveCharacters() const;
    bool IsBattleOver() const;

    // 도전 4
    Character* FindFirstAliveCharacter();
    Character* FindSecondAliveCharacter();

private:
    std::vector<std::unique_ptr<Character>> m_characters;
    int m_turnCount;
    std::mt19937 m_randomEngine;
    std::uniform_int_distribution<int> m_criticalRoll;
};
