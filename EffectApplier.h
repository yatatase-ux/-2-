#pragma once
#include "BattleMonster.h"
#include "MoveData.h"

class EffectApplier
{
public:
	void ApplyStatChange(BattleMonster& target, StatType stat, int change);
	void ApplyStatusCondition(BattleMonster& target, EffectType effect);
	void ResetBattleRanks(BattleMonster& mon);
	float RankToMultiplier(int rank);

	int GetRank(const BattleMonster& target, StatType stat) const;
};