#pragma once
#include "DamageCalculator.h"

enum class BattleState
{
    COMMAND,
    MOVE_SELECT,
    ACTION,
    END
};

class BattleManager
{
protected:

    BattleState state = BattleState::COMMAND;

public:

	BattleManager();



};

