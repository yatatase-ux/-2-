#pragma once
#include "BattleMonster.h"
#include "CpuBrain.h"

struct BattleContext
{
    BattleMonster* player = nullptr;
    BattleMonster* enemy  = nullptr;

    BattleMonster* faintedMonster = nullptr;

    bool isPlayerWin = false;

    bool isForcedSwitch = false;

    MoveScoreDebug enemyMoveScore[4];

    SwitchScoreDebug enemySwitchScore[MEMBER_MAX - 1];
};