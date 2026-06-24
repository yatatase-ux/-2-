#include "ButtleManager.h"

Buttle::Buttle()
{

}

int Buttle::CalcDamage(
    const BasicState& attacker,
    const BasicState& defender,
    int moveID)
{
    const MoveData& move = MoveTable[moveID];

    int atk = attacker.PATK;
    int def = defender.PDEF;

    int damage =
        (move.Power * atk) / def;

    return damage;
}

bool Buttle::CheckHit()
{
    return false;
}

void Buttle::ApplyDamage()
{

}