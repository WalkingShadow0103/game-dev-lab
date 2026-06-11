#include "Character.h"

#include <iostream>

Character::Character()
    : m_name("Unknown")
    , m_hp(100)
    , m_maxHp(100)
    , m_attackPower(10)
    , m_state(CharacterState::Idle)
{
}

Character::Character(const std::string& name, int maxHp, int attackPower)
    : m_name(name)
    , m_hp(maxHp)
    , m_maxHp(maxHp)
    , m_attackPower(attackPower)
    , m_state(CharacterState::Idle)
{
    if (m_maxHp <= 0)
    {
        m_maxHp = 1;
        m_hp = 1;
    }

    if (m_attackPower < 0)
    {
        m_attackPower = 0;
    }

    ClampHp();
    UpdateDeadState();
}

const std::string& Character::GetName() const
{
    return m_name;
}

int Character::GetHp() const
{
    return m_hp;
}

int Character::GetMaxHp() const
{
    return m_maxHp;
}

int Character::GetAttackPower() const
{
    return m_attackPower;
}

CharacterState Character::GetState() const
{
    return m_state;
}

bool Character::IsDead() const
{
    return m_state == CharacterState::Dead;
}

bool Character::CanAct() const
{
    return !IsDead();
}

void Character::TakeDamage(int damage)
{
    if (damage < 0)
    {
        std::cout << "Damage cannot be negative.\n";
        return;
    }

    if (IsDead())
    {
        std::cout << m_name << " is already dead.\n";
        return;
    }

    m_hp -= damage;

    ClampHp();

    if (m_hp <= 0)
    {
        m_state = CharacterState::Dead;
    }
    else
    {
        m_state = CharacterState::Hit;
    }
    //UpdateDeadState(); Hit 관련 문제로 일단 주석화

    std::cout << m_name << " took " << damage
        << " damage. HP: " << m_hp << "/" << m_maxHp << "\n";
}

void Character::Heal(int amount)
{
    if (amount < 0)
    {
        std::cout << "Heal amount cannot be negative.\n";
        return;
    }

    if (IsDead())
    {
        std::cout << "Dead character cannot be healed: " << m_name << "\n";
        return;
    }

    m_hp += amount;

    ClampHp();

    std::cout << m_name << " healed " << amount
        << ". HP: " << m_hp << "/" << m_maxHp << "\n";
}

void Character::SetState(CharacterState state)
{
    if (IsDead() && state != CharacterState::Dead)
    {
        std::cout << "Dead character cannot change state: " << m_name << "\n";
        return;
    }

    m_state = state;
}

void Character::Print() const
{
    std::cout << m_name
        << " | HP: " << m_hp << "/" << m_maxHp
        << " | ATK: " << m_attackPower
        << " | State: " << ToString(m_state)
        << "\n";
}

void Character::ClampHp()
{
    if (m_hp < 0)
    {
        m_hp = 0;
    }

    if (m_hp > m_maxHp)
    {
        m_hp = m_maxHp;
    }
}

void Character::UpdateDeadState()
{
    if (m_hp <= 0)
    {
        m_state = CharacterState::Dead;
    }
}
