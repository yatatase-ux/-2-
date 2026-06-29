#include "BattleManager.h"
#include "DxLib.h"

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
    if (moveID < 0 || moveID >= MoveTableSize)
    {
        return 0;
    }

    const MoveData& move = MoveTable[moveID];

    int atk = 0;
    int def = 0;
    switch (move.category)
    {
    case PHYSICAL:
        atk = attacker.PATK;
        def = defender.PDEF;
        break;
    case SPECIAL:
        atk = attacker.MATK;
        def = defender.MDEF;
        break;
    case STATUS:
        return 0;
    }

    if (def <= 0)
    {
        def = 1;
    }

    float damage = BaseDamage(move.Power, atk, def);

    damage *= TypeBonus(attacker, move);

    damage *= TypeMatchup(defender, move);

    if (damage <= 0.0f)
    {
        return 0;
    }

    return (int)damage;
}

bool BattleManager::CheckHit()
{
    return false;
}

void BattleManager::ApplyDamage()
{

}

float  BattleManager::BaseDamage(int power, int atk, int def)
{
    return (power * atk) / (float)max(def, 1);
}

float BattleManager::TypeBonus(const MonsterBaseData& attacker, const MoveData& move)
{

    for (int type = 0; type < 2; type++)
    {
        if (attacker.element[type] == move.element)
        {
            return 1.5f;
        }
    }

    return 1.0f;
}

float BattleManager::TypeMatchup(const MonsterBaseData& defender, const MoveData& move)
{
    float mag = 1.0f;
    for (int type = 0; type < 2; type++)
    {
        mag *= TypeTable[(int)move.element][(int)defender.element[type]];
    }

    return mag;
}
