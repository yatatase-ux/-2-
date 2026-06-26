#pragma once
#include "MonsterBaseData.h"
#include "MoveData.h"

class BattleManager
{
protected:

public:

	BattleManager();

	/// <summary>
	/// ダメージ計算
	/// </summary>
	/// <param name="attacker">攻め</param>
	/// <param name="defender">受け</param>
	/// <param name="moveID">技の番号</param>
	/// <returns>ダメージ量</returns>
	int CalcDamage(
		const MonsterBaseData& attacker,
		const MonsterBaseData& defender,
		int moveID);

	bool CheckHit();

	void ApplyDamage();
};