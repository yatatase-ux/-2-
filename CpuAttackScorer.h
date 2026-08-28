#pragma once
#include "BattleMonster.h"
#include "DamageCalculator.h"
#include "Party.h"
#include "CpuRiskEvaluator.h"
#include "EffectApplier.h"

class CpuAttackScorer
{
private:

	CpuRiskEvaluator riskEvaluator;
	EffectApplier effect;
	
public:

	int Score(int moveID, BattleMonster& self, BattleMonster& opponent,
          Members& opponentMembers, DamageCalculator& damageCalc,
          bool isMatchPoint, bool opponentPredictedToSwitch = false);

	float BenchConsistencyScore(const MoveData& move, BattleMonster& activeOpponent,
								Members& opponentMembers, DamageCalculator& damageCalc);

};