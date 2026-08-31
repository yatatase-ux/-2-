#pragma once
#include "BattleMonster.h"
#include "EffectApplier.h"
#include "Party.h"
#include "DamageCalculator.h"

#include "CpuAttackScorer.h"
#include "CpuStatusScorer.h"
#include "CpuSwitchScorer.h"
#include "CpuDebugTypes.h" 
#include "CpuRiskEvaluator.h"

class CpuBrain
{
private:
	CpuAttackScorer attackScorer;
	CpuStatusScorer statusScorer;
	CpuSwitchScorer switchScorer;
	EffectApplier effect;

public:

	int ScoreMove(int moveID, const CpuEvalContext& ctx);

	CpuDecisionResult Decide(CpuEvalContext ctx, bool checkOscillation = true);

};