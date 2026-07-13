#pragma once
#include "BattleMonster.h"

struct BattleContext
{
    BattleMonster* player = nullptr;
    BattleMonster* enemy  = nullptr;

    int selectedMoveID = -1;
    int changeMonster = -1;
};