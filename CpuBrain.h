#pragma once
#include "CpuAttackScorer.h"
#include "CpuStatusScorer.h"

class CpuBrain
{
private:

	CpuAttackScorer attackScorer;
	CpuStatusScorer statusScorer;

public:

	int ChooseMove(BattleMonster& self, BattleMonster& opponent,
		DamageCalculator& damageCalc, EffectApplier& effect, bool isMatchPoint);

};