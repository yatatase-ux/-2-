#pragma once
#include "BattleMonster.h"
#include "DamageCalculator.h"
#include "EffectApplier.h"

class CpuRiskEvaluator
{
public:
	// 瀕死リスクの推定
	float EstimateKORisk(BattleMonster& self, BattleMonster& opponent, DamageCalculator& damageCalc);
	// 与ダメージ量の推定
	float EstimateBestExpectedDamage(BattleMonster& attacker, BattleMonster& defender, DamageCalculator& damageCalc);
};