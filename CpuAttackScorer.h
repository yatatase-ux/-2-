#pragma once
#include "BattleMonster.h"
#include "DamageCalculator.h"
#include "Party.h"

struct MoveScoreDebug
{
	int moveID;
	int score;
};

class CpuAttackScorer
{
private:
	
public:
	int Score(int moveID, BattleMonster& self, BattleMonster& opponent, DamageCalculator& damageCalc, bool isMatchPoint);

	MoveScoreDebug lastScores[4]; // ’¼‹ß‚Ì•]‰¿Œ‹‰Ê‚ğ•Û

//	float BenchConsistencyScore(const MoveData& move, const Members& enemyBox);

	float EstimateKORisk(BattleMonster& self, BattleMonster& opponent, DamageCalculator& damageCalc);
	
	int ChooseMove(BattleMonster& self, BattleMonster& opponent, DamageCalculator& damageCalc);

};