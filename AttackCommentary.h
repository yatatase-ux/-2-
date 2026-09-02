#pragma once
#include "CommentarySituation.h"
#include "BattleMonster.h"
#include "DamageCalculator.h"
#include "CpuRiskEvaluator.h"
#include "EffectApplier.h"

class AttackCommentary
{
private:
	CpuRiskEvaluator riskEvaluator;
	EffectApplier effect;

public:

	CommentarySituation Classify(BattleMonster& self, BattleMonster& opponent, int moveID,
									DamageCalculator& damageCalc, bool isMatchPoint);
};

