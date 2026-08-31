#pragma once
#include "BattleMonster.h"
#include "DamageCalculator.h"
#include "EffectApplier.h"
#include "CpuRiskEvaluator.h"
#include "CpuEvalContext.h"

class CpuSwitchScorer
{
private:
	CpuRiskEvaluator riskEvaluator;
	EffectApplier effect;
public:

	int Score(const CpuEvalContext& ctx, BattleMonster& candidate);
};