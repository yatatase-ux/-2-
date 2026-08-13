#include "DamageCalculator.h"
#include "DxLib.h"

DamageCalculator::DamageCalculator()
{

}

/// <summary>
/// ダメージ処理
/// </summary>
/// <param name="attacker">攻撃側</param>
/// <param name="defender">受け側</param>
/// <param name="moveID">技ID</param>
void DamageCalculator::Attack(BattleMonster& attacker, BattleMonster& defender, int moveID)
{
    int damage = CalcDamage(attacker, defender, moveID);

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
int DamageCalculator::CalcDamage(
    const BattleMonster& attacker,
    const BattleMonster& defender,
    int moveID)
{
    if (moveID < 0 || moveID >= MoveTableSize)
    {
        return 0;
    }
    const MoveData& move = MoveTable[moveID];

    int atk = 0;
    int def = 0;
    int atkRank = 0;
    int defRank = 0;

    switch (move.category)
    {
    case MoveCategory::Physical:
        atk = attacker.data->PATK;
        def = defender.data->PDEF;
        atkRank = attacker.PATKRank;
        defRank = defender.PDEFRank;
        break;
    case MoveCategory::Special:
        atk = attacker.data->MATK;
        def = defender.data->MDEF;
        atkRank = attacker.MATKRank;
        defRank = defender.MDEFRank;
        break;
    case MoveCategory::Status:
        return 0;
    }

    // ランク補正を反映
    atk = (int)(atk * effect.RankToMultiplier(atkRank));
    def = (int)(def * effect.RankToMultiplier(defRank));

    if (def <= 0)
    {
        def = 1;
    }

    float damage = BaseDamage(move.Power, atk, def);
    damage *= TypeBonus(*attacker.data, move);
    damage *= TypeMatchup(*defender.data, move);

    if (damage <= 0.0f)
    {
        return 0;
    }
    return (int)damage;
}

// 将来的に実装する乱数
//int DamageCalculator::RollDamage(const BattleMonster& attacker, const BattleMonster& defender, int moveID)
//{
//    int baseDamage = CalcDamage(attacker, defender, moveID); // 基準値の計算はそのまま流用
//    float roll = 0.85f + (GetRand(15) / 100.0f); // 例:85%~100%の乱数
//    return (int)(baseDamage * roll);
//}

float DamageCalculator::LethalProbability(const BattleMonster& attacker, const BattleMonster& defender, int moveID)
{
    const MoveData& move = MoveTable[moveID];
    if (move.category == MoveCategory::Status) return 0.0f;

    int dmg = CalcDamage(attacker, defender, moveID);
    bool isLethal = (dmg >= defender.CurrentHP);

    return isLethal ? (move.Accuracy / 100.0f) : 0.0f;
}

bool DamageCalculator::CheckHit()
{
    return false;
}

void DamageCalculator::ApplyDamage()
{

}

float  DamageCalculator::BaseDamage(int power, int atk, int def)
{
    const float scale = 4.0f; // 仮の値。プレイテストしながら調整
    return (power * atk) / (float)max(def, 1) / scale;

}

float DamageCalculator::TypeBonus(const MonsterBaseData& attacker, const MoveData& move)
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

float DamageCalculator::TypeMatchup(const MonsterBaseData& defender, const MoveData& move)
{
    float mag = 1.0f;
    for (int type = 0; type < 2; type++)
    {
        mag *= TypeTable[(int)move.element][(int)defender.element[type]];
    }

    return mag;
}
