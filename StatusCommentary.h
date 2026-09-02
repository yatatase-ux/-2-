#pragma once
#include "CommentarySituation.h"
#include "BattleMonster.h"
#include "DamageCalculator.h"
#include "CpuRiskEvaluator.h"


class StatusCommentary
{
private:

	CpuRiskEvaluator riskEvaluator;

public:

	CommentarySituation Classify(BattleMonster& self, BattleMonster& opponent, int moveID, DamageCalculator& damageCalc);

};
