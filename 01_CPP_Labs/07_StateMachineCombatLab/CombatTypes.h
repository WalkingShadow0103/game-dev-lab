#pragma once

#include <string>

enum class CharacterState
{
    Idle,
    Attacking,
    // 도전 1: Hit 상태 추가
    Hit,
    Dead
};

enum class BattleResult
{
    None,
    Hit,
    TargetDead,
    InvalidAttacker,
    InvalidTarget
};

std::string ToString(CharacterState state);
std::string ToString(BattleResult result);
