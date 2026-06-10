#pragma once

#include <string>
#include <vector>

struct Character
{
    std::string name;
    int hp;
    int maxHp;
    int attackPower;

    Character();
    Character(const std::string& characterName, int characterMaxHp, int characterAttackPower);

    bool IsDead() const;
};

void PrintCharacter(const Character& character);
void PrintParty(const std::vector<Character>& characters);

void DamageByValue(Character character, int damage);
void DamageByReference(Character& character, int damage);
bool DamageByPointer(Character* character, int damage);

bool HealByPointer(Character* character, int amount);

Character* FindCharacterByName(
    std::vector<Character>& characters,
    const std::string& name
);

void PrintAddressDemo(Character& character);
void RunPassingDemo();

Character* FindLowestHpCharacter(
    std::vector<Character>& characters
);

bool ReviveByPointer(
    Character* character, int reviveHp
);
