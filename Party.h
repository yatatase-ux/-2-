#pragma once
#include "BattleMonster.h"

const int PARTY_MAX = 6;
const int MEMBER_MAX = 3;

struct Party
{
    BattleMonster mons[PARTY_MAX];
};

struct Members
{
    BattleMonster* mons[MEMBER_MAX];

    int current = 0;

    BattleMonster* Active()
    {
        return mons[current];
    }

};