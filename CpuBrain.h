#pragma once
#include "BattleMonster.h"
#include "DamageCalculator.h"
#include "Party.h"

struct MoveScoreDebug
{
	int moveID;
	int score;
};

class CpuBrain
{
private:
	
public:
	int ScoreMove(int moveID, BattleMonster& self, BattleMonster& opponent, DamageCalculator& damageCalc);

	MoveScoreDebug lastScores[4]; // íºãﬂÇÃï]âøåãâ Çï€éù

//	float BenchConsistencyScore(const MoveData& move, const Members& enemyBox);

	float EstimateKORisk(BattleMonster& self, BattleMonster& opponent, DamageCalculator& damageCalc);
	
	int ChooseMove(BattleMonster& self, BattleMonster& opponent, DamageCalculator& damageCalc);

	MoveScoreDebug* GetLastScore(int num);

};