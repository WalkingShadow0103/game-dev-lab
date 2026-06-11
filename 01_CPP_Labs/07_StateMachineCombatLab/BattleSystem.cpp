#include "BattleSystem.h"

#include <iostream>
#include <random>

BattleSystem::BattleSystem()
    : m_characters()
    , m_turnCount(1)
    , m_randomEngine(std::random_device{}())
    , m_criticalRoll(0,99)
{
}

void BattleSystem::AddCharacter(const std::string& name, int maxHp, int attackPower)
{
    if (name.empty())
    {
        std::cout << "Character name cannot be empty.\n";
        return;
    }

    if (FindCharacterByName(name) != nullptr)
    {
        std::cout << "Character already exists: " << name << "\n";
        return;
    }

    m_characters.push_back(std::make_unique<Character>(name, maxHp, attackPower));

    std::cout << "Added character: " << name << "\n";
}

Character* BattleSystem::FindCharacterByName(const std::string& name)
{
    for (std::unique_ptr<Character>& character : m_characters)
    {
        if (character == nullptr)
        {
            continue;
        }

        if (character->GetName() == name)
        {
            return character.get();
        }
    }

    return nullptr;
}

const Character* BattleSystem::FindCharacterByName(const std::string& name) const
{
    for (const std::unique_ptr<Character>& character : m_characters)
    {
        if (character == nullptr)
        {
            continue;
        }

        if (character->GetName() == name)
        {
            return character.get();
        }
    }

    return nullptr;
}

BattleResult BattleSystem::Attack(const std::string& attackerName, const std::string& targetName)
{

    Character* attacker = FindCharacterByName(attackerName);

    if (attacker == nullptr || attacker->IsDead()) {
        std::cout << "Invalid attacker: " << attackerName << "\n";
        return BattleResult::InvalidAttacker;
    }

    Character* target = FindCharacterByName(targetName);

    if (target == nullptr || target->IsDead()) {
        std::cout << "Invalid target: " << targetName << "\n";
        return BattleResult::InvalidTarget;
    }

    attacker->SetState(CharacterState::Attacking);

    std::cout << "[Turn " << m_turnCount << "] " // 도전 3. 전투 로그 카운터
        << attacker->GetName()
        << " attacks "
        << target->GetName()
        << "!\n";

    m_turnCount++;

    bool isCritical = m_criticalRoll(m_randomEngine) < 20;

    if (isCritical) // 20% 확률.
    {
        std::cout << "Critical hit!\n";
        target->TakeDamage(attacker->GetAttackPower()*2); // 도전 2. 크리티컬이면 두배.
    }
    else
    {
        target->TakeDamage(attacker->GetAttackPower());
    }

    attacker->SetState(CharacterState::Idle);

    if (target->IsDead())
    {
        std::cout << target->GetName() << " is dead.\n";
        return BattleResult::TargetDead;
    }
    target->SetState(CharacterState::Idle);
    return BattleResult::Hit;
}

bool BattleSystem::Heal(const std::string& targetName, int amount)
{
    Character* target = FindCharacterByName(targetName);

    if (target == nullptr)
    {
        std::cout << "Target not found: " << targetName << "\n";
        return false;
    }

    target->Heal(amount);
    return true;
}

void BattleSystem::PrintAllCharacters() const
{
    std::cout << "=== Characters ===\n";

    if (m_characters.empty())
    {
        std::cout << "No characters.\n";
        return;
    }

    for (std::size_t i = 0; i < m_characters.size(); ++i)
    {
        std::cout << i << ". ";

        if (m_characters[i] == nullptr)
        {
            std::cout << "null character\n";
            continue;
        }

        m_characters[i]->Print();
    }
}

void BattleSystem::PrintAliveCharacters() const
{
    std::cout << "=== Alive Characters ===\n";

    bool foundAlive = false;

    for (const std::unique_ptr<Character>& character : m_characters)
    {
        if (character == nullptr)
        {
            continue;
        }

        if (!character->IsDead())
        {
            character->Print();
            foundAlive = true;
        }
    }

    if (!foundAlive)
    {
        std::cout << "No alive characters.\n";
    }
}

bool BattleSystem::IsBattleOver() const
{
    int aliveCount = 0;

    for (const std::unique_ptr<Character>& character : m_characters)
    {
        if (character != nullptr && !character->IsDead())
        {
            ++aliveCount;
        }
    }

    return aliveCount <= 1;
}

Character* BattleSystem::FindFirstAliveCharacter()
{
    for (const std::unique_ptr<Character>& character : m_characters)
    {
        if (!character->IsDead()) {
            return character.get();
        }
    }
    return nullptr;
}
Character* BattleSystem::FindSecondAliveCharacter()
{
    int aliveCounter = 0;
    for (const std::unique_ptr<Character>& character : m_characters)
    {
        if (!character->IsDead() && aliveCounter == 1)
        {
            return character.get();
        }
        else if(!character->IsDead())
        {
            aliveCounter++;
        }
    }
    return nullptr;
}
