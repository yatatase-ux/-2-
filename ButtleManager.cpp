#include "BattleManager.h"

BattleManager::BattleManager()
{

}

/// <summary>
/// ダメージ処理
/// </summary>
/// <param name="attacker">攻撃側</param>
/// <param name="defender">受け側</param>
/// <param name="moveID">技ID</param>
void BattleManager::Attack(BattleMonster& attacker, BattleMonster& defender, int moveID)
{
    int damage = CalcDamage(*attacker.data, *defender.data, moveID);

    defender.CurrentHP -= damage;

    if (defender.CurrentHP < 0)
        defender.CurrentHP = 0;
}

/// <summary>
/// ダメージ計算
/// </summary>
/// <param name="attacker">攻め</param>
/// <param name="defender">受け</param>
/// <param name="moveID">技の番号</param>
/// <returns>ダメージ量</returns>
int BattleManager::CalcDamage(
    const MonsterBaseData& attacker,
    const MonsterBaseData& defender,
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

bool BattleManager::CheckHit()
{
    return false;
}

void BattleManager::ApplyDamage()
{

}