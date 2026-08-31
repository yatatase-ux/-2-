#pragma once
#include "BattleMonster.h"
#include "DamageCalculator.h"
#include "EffectApplier.h"
#include "CpuRiskEvaluator.h"
#include "CpuEvalContext.h"

class CpuStatusScorer
{
private:
	CpuRiskEvaluator riskEvaluator;
	EffectApplier effect; // ctx‚Å‚Í‚È‚­©‘O‚Å‚Â

	int CalcBestDamage(BattleMonster& attacker, BattleMonster& defender,
						DamageCalculator& damageCalc);

public:
	int Score(int moveID, const CpuEvalContext& ctx);
};