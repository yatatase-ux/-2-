#pragma once
#include "BattleMonster.h"
#include "DamageCalculator.h"
#include "Party.h"
#include "CpuRiskEvaluator.h"
#include "EffectApplier.h"
#include "CpuEvalContext.h"

class CpuAttackScorer
{
private:

	CpuRiskEvaluator riskEvaluator;
	EffectApplier effect;
	
public:

	int Score(int moveID, const CpuEvalContext& ctx);

	float BenchConsistencyScore(const MoveData& move, BattleMonster& activeOpponent,
								Members& opponentMembers, DamageCalculator& damageCalc);

};