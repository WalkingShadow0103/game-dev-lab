#pragma once

#include <string>

#include "CombatTypes.h"

class Character
{
public:
    Character();
    Character(const std::string& name, int maxHp, int attackPower);

    const std::string& GetName() const;
    int GetHp() const;
    int GetMaxHp() const;
    int GetAttackPower() const;
    CharacterState GetState() const;

    bool IsDead() const;
    bool CanAct() const;

    void TakeDamage(int damage);
    void Heal(int amount);

    void SetState(CharacterState state);
    void Print() const;

private:
    void ClampHp();
    void UpdateDeadState();

private:
    std::string m_name;
    int m_hp;
    int m_maxHp;
    int m_attackPower;
    CharacterState m_state;
};
