#include "Character.h"

#include <algorithm>
#include <iostream>

Character::Character()
    : name("Unknown")
    , hp(100)
    , maxHp(100)
    , attackPower(10)
{
}

Character::Character(
    const std::string& characterName,
    int characterMaxHp,
    int characterAttackPower
)
    : name(characterName)
    , hp(characterMaxHp)
    , maxHp(characterMaxHp)
    , attackPower(characterAttackPower)
{
    if (maxHp <= 0)
    {
        maxHp = 1;
        hp = 1;
    }

    if (attackPower < 0)
    {
        attackPower = 0;
    }
}

bool Character::IsDead() const
{
    return hp <= 0;
}

void PrintCharacter(const Character& character)
{
    std::cout << character.name
        << " | HP: " << character.hp << "/" << character.maxHp
        << " | ATK: " << character.attackPower
        << " | Dead: " << (character.IsDead() ? "Yes" : "No")
        << "\n";
}

void PrintParty(const std::vector<Character>& characters)
{
    std::cout << "=== Party ===\n";

    if (characters.empty())
    {
        std::cout << "Party is empty.\n";
        return;
    }

    for (std::size_t i = 0; i < characters.size(); ++i)
    {
        std::cout << i << ". ";
        PrintCharacter(characters[i]);
    }
}

void DamageByValue(Character character, int damage)
{
    if (damage < 0)
    {
        return;
    }

    character.hp -= damage;

    if (character.hp < 0)
    {
        character.hp = 0;
    }

    std::cout << "[Value] Damaged copy of " << character.name
        << " for " << damage << ". Copy HP: " << character.hp << "\n";
}

void DamageByReference(Character& character, int damage)
{

    if (damage < 0)
    {
        return;
	}

	character.hp -= damage;

    if (character.hp < 0)
    {
        character.hp = 0;
    }

    std::cout << "[Reference] Damaged " << character.name
		<< " for " << damage << ". HP: " << character.hp << "\n";
}

bool DamageByPointer(Character* character, int damage)
{

    if (character == nullptr)
    {
        std::cout << "[Pointer] target is null.\n";
        return false;
    }

    if (damage < 0)
    {
        std::cout << "[Pointer] damage cannot be negative.\n";
        return false;
	}

    character->hp -= damage;

    if (character->hp < 0)
    {
        character->hp = 0;
	}

	std::cout << "[Pointer] Damaged " << character->name
		<< " for " << damage << ". HP: " << character->hp << "\n";

    return true;
}

bool HealByPointer(Character* character, int amount)
{

    if (character == nullptr)
    {
        std::cout << "[Pointer] target is null.\n";
        return false;
	}

    if (amount < 0)
    {
        std::cout << "[Pointer] heal amount cannot be negative.\n";
        return false;
    }

	character->hp += amount;

    if (character->hp > character->maxHp)
    {
		character->hp = character->maxHp;
	}

	std::cout << "[Pointer] Healed " << character->name
		<< " for " << amount << ". HP: " << character->hp << "\n";

    return true;
}

Character* FindCharacterByName(
    std::vector<Character>& characters,
    const std::string& name
)
{
    for (Character& character : characters)
    {
        if (character.name == name)
        {
            return &character;
        }
	}

    return nullptr;
}

void PrintAddressDemo(Character& character)
{
    std::cout << "=== Address Demo ===\n";
    std::cout << "Character name: " << character.name << "\n";
    std::cout << "Object address: " << &character << "\n";
    std::cout << "hp address: " << &character.hp << "\n";
    std::cout << "maxHp address: " << &character.maxHp << "\n";
    std::cout << "attackPower address: " << &character.attackPower << "\n";
}

void RunPassingDemo()
{
    std::cout << "=== Passing Demo ===\n";

    Character dummy("TrainingDummy", 100, 0);

    std::cout << "Initial: ";
    PrintCharacter(dummy);

    DamageByValue(dummy, 30);
    std::cout << "After DamageByValue: ";
    PrintCharacter(dummy);

    DamageByReference(dummy, 30);
    std::cout << "After DamageByReference: ";
    PrintCharacter(dummy);

    DamageByPointer(&dummy, 30);
    std::cout << "After DamageByPointer: ";
    PrintCharacter(dummy);

    DamageByPointer(nullptr, 30);
}

Character* FindLowestHpCharacter(std::vector<Character>& characters)
{
    // 도전 1: 가장 HP가 낮은 캐릭터 찾기
    // party가 비어있으면 nullptr 반환
    // 캐릭터가 있으면 현재 hp가 가장 낮은 캐릭터의 포인터 반환
    // 동점이면 먼저 발견한 캐릭터 반환
    // 메뉴 추가: 6. Print lowest HP character

    if (characters.empty())
    {
        return nullptr;
	}

    Character* lowestHpCharacter = &characters[0];

    for (Character& character : characters)
    {
        if (character.hp < lowestHpCharacter->hp)
        {
            lowestHpCharacter = &character;
        }
    }
	return lowestHpCharacter;
}

bool ReviveByPointer(Character* character, int reviveHp)
{
    // 도전 2: 죽은 캐릭터 회복 제한
	// HP가 0인 캐릭터는 HealByPointer로 회복할 수 없다.
    // ReviveByPointer로만 회복할 수 있다.
    // character가 nullptr이면 실패
    // reviveHp <= 0이면 실패
    // 캐릭터가 죽지 않았으면 실패
    // 캐릭터가 죽어있으면 hp를 reviveHp로 설정하고 true 반환
	// reviveHp가 maxHP보다 크면 maxHp로 보정
    if (character == nullptr)
    {
        std::cout << "[Revive] target is null.\n";
        return false;
    }
    if (reviveHp <= 0)
    {
        std::cout << "[Revive] revive HP must be positive.\n";
        return false;
    }
    if (!character->IsDead())
    {
        std::cout << "[Revive] character is not dead.\n";
        return false;
    }
	character->hp = std::min(reviveHp, character->maxHp);
    std::cout << "[Revive] Revived " << character->name
        << " with " << character->hp << " HP.\n";
	return true;
}
