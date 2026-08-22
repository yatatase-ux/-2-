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
	int Score(int moveID, BattleMonster& self, BattleMonster& opponent, DamageCalculator& damageCalc, bool isMatchPoint);

//	float BenchConsistencyScore(const MoveData& move, const Members& enemyBox);

};