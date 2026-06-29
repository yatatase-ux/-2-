#pragma once
#include "MonsterBaseData.h"
#include "MoveData.h"
#include "BattleMonster.h"

class DamageCalculator
{
protected:

public:

	DamageCalculator();

	/// <summary>
	/// ダメージ処理
	/// </summary>
	/// <param name="attacker">攻撃側</param>
	/// <param name="defender">受け側</param>
	/// <param name="moveID">技ID</param>
	void Attack(BattleMonster& attacker,
		BattleMonster& defender,
		int moveID);

	/// <summary>
	/// ダメージ計算
	/// </summary>
	/// <param name="attacker">攻め</param>
	/// <param name="defender">受け</param>
	/// <param name="moveID">技ID</param>
	/// <returns>ダメージ量</returns>
	int CalcDamage(
		const MonsterBaseData& attacker,
		const MonsterBaseData& defender,
		int moveID);

	bool CheckHit();

	void ApplyDamage();

	float BaseDamage(int power, int atk, int def);

	float TypeBonus(const MonsterBaseData& attacker, const MoveData& move);

	float TypeMatchup(const MonsterBaseData& defender, const MoveData& move);

};