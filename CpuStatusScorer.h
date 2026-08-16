#pragma once
#include "BattleMonster.h"
#include "DamageCalculator.h"
#include "EffectApplier.h"
#include "CpuRiskEvaluator.h"

class CpuStatusScorer
{
private:
	CpuRiskEvaluator riskEvaluator; // é©ëOÇ≈ï€éù
public:
	int Score(int moveID, BattleMonster& self, BattleMonster& opponent,
		DamageCalculator& damageCalc, EffectApplier& effect);
};