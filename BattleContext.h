#pragma once
#include "BattleMonster.h"
#include "CpuAttackScorer.h"

struct BattleContext
{
    BattleMonster* player = nullptr;
    BattleMonster* enemy  = nullptr;

    BattleMonster* faintedMonster = nullptr;

    bool isPlayerWin = false;

    bool isForcedSwitch = false;

    MoveScoreDebug enemyMoveScores[4];
};