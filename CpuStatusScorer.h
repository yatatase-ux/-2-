#pragma once
#include "BattleMonster.h"
#include "DamageCalculator.h"
#include "EffectApplier.h"

class CpuStatusScorer
{
private:

public:
	int Score(int moveID, BattleMonster& self, BattleMonster& opponent,
		DamageCalculator& damageCalc, EffectApplier& effect);

};