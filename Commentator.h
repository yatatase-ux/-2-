#pragma once
#include "CommentarySituation.h"
#include "BattleMonster.h"
#include "DamageCalculator.h"
#include "CpuRiskEvaluator.h"
#include "EffectApplier.h"

#include "AttackCommentary.h"
#include "StatusCommentary.h"

class Commentator
{
private:
	DamageCalculator damageCalc;
	AttackCommentary attackClassifier;
	StatusCommentary statusClassifier;

	CommentarySituation Classify(BattleMonster& self, BattleMonster& opponent, int moveID, bool isMatchPoint);
	const char* PickLine(CommentarySituation situation);

public:

	const char* Comment(BattleMonster& self, BattleMonster& opponent, int moveID, bool isMatchPoint);

};