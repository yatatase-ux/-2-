#pragma once
#include "BattleMonster.h"
#include "DamageCalculator.h"
#include "EffectApplier.h"
#include "CpuRiskEvaluator.h"

class CpuStatusScorer
{
private:
	CpuRiskEvaluator riskEvaluator;
	int CalcBestDamage(BattleMonster& attacker, BattleMonster& defender,
						DamageCalculator& damageCalc);

public:
	int Score(int moveID, BattleMonster& self, BattleMonster& opponent,
		DamageCalculator& damageCalc, EffectApplier& effect);
};