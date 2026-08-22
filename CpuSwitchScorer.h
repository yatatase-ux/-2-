#pragma once
#include "BattleMonster.h"
#include "DamageCalculator.h"
#include "EffectApplier.h"
#include "CpuRiskEvaluator.h"

class CpuSwitchScorer
{
private:
	CpuRiskEvaluator riskEvaluator;
	EffectApplier effect;
public:
	int Score(BattleMonster& self, BattleMonster& opponent, BattleMonster& candidate, DamageCalculator& damageCalc);
};