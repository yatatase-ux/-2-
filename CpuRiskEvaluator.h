#pragma once
#include "BattleMonster.h"
#include "DamageCalculator.h"
#include "EffectApplier.h"

class CpuRiskEvaluator
{
public:
	float EstimateKORisk(BattleMonster& self, BattleMonster& opponent, DamageCalculator& damageCalc);
};