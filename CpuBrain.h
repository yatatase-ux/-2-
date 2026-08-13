#pragma once
#include "BattleMonster.h"
#include "DamageCalculator.h"
#include "Party.h"

class CpuBrain
{
private:
	int ScoreMove(int moveID, BattleMonster& self, BattleMonster& opponent, DamageCalculator& damageCalc);

public:
//	float BenchConsistencyScore(const MoveData& move, const Members& enemyBox);

	float EstimateKORisk(BattleMonster& self, BattleMonster& opponent, DamageCalculator& damageCalc);
	
	int ChooseMove(BattleMonster& self, BattleMonster& opponent, DamageCalculator& damageCalc);

};