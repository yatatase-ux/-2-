#include "ButtleManager.h"

ButtleManager::ButtleManager()
{

}

int ButtleManager::CalcDamage(
    const BasicState& attacker,
    const BasicState& defender,
    int moveID)
{
    if (moveID < 0)
    {
        return 0;
    }

    const MoveData& move = MoveTable[moveID];

    int atk = attacker.PATK;
    int def = defender.PDEF;

    if (def <= 0)
    {
        def = 1;
    }

    int damage =
        (move.Power * atk) / def;

    return damage;
}

bool ButtleManager::CheckHit()
{
    return false;
}

void ButtleManager::ApplyDamage()
{

}