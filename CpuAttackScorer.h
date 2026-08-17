#pragma once
#include "BattleMonster.h"
#include "DamageCalculator.h"
#include "Party.h"
#include "CpuRiskEvaluator.h"

struct MoveScoreDebug
{
	int moveID;
	int score;
};

class CpuAttackScorer
{
private:

	CpuRiskEvaluator riskEvaluator;
	
public:
	int Score(int moveID, BattleMonster& self, BattleMonster& opponent, DamageCalculator& damageCalc, bool isMatchPoint);

//	float BenchConsistencyScore(const MoveData& move, const Members& enemyBox);

	int ChooseMove(BattleMonster& self, BattleMonster& opponent, DamageCalculator& damageCalc);

};