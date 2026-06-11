#include "CombatTypes.h"

std::string ToString(CharacterState state)
{
    switch (state)
    {
    case CharacterState::Idle:
        return "Idle";

    case CharacterState::Attacking:
        return "Attacking";

    case CharacterState::Dead:
        return "Dead";

    default:
        return "Unknown";
    }
}

std::string ToString(BattleResult result)
{
    switch (result)
    {
    case BattleResult::None:
        return "None";

    case BattleResult::Hit:
        return "Hit";

    case BattleResult::TargetDead:
        return "TargetDead";

    case BattleResult::InvalidAttacker:
        return "InvalidAttacker";

    case BattleResult::InvalidTarget:
        return "InvalidTarget";

    default:
        return "Unknown";
    }
}
