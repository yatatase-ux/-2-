#pragma once
#include "BattleMonster.h"
#include "EffectApplier.h"
#include "Party.h"
#include "DamageCalculator.h"

#include "CpuAttackScorer.h"
#include "CpuStatusScorer.h"
#include "CpuSwitchScorer.h"
#include "CpuDebugTypes.h" 

struct CpuDecisionResult
{
	int selectedMoveID = -1; // ‹Z‚ğ‘I‚ñ‚¾ê‡
	int switchToIndex = -1;  // Œğ‘ã‚ğ‘I‚ñ‚¾ê‡(Members“à‚Ìindex)
	MoveScoreDebug moveScores[MOVE_SLOT_MAX];
	SwitchScoreDebug switchScores[MEMBER_MAX - 1]; // T‚¦‚Ì”(Œ»ó2)
};

class CpuBrain
{
private:
	CpuAttackScorer attackScorer;
	CpuStatusScorer statusScorer;
	CpuSwitchScorer switchScorer;
	EffectApplier effect;

public:

	int ScoreMove(int moveID, BattleMonster& self, BattleMonster& opponent, Members& opponentMembers,
		DamageCalculator& damageCalc, bool isMatchPoint, bool opponentPredictedToSwitch = false);

	CpuDecisionResult Decide(BattleMonster& self, BattleMonster& opponent, Members& selfMembers,
		Members& opponentMembers, DamageCalculator& damageCalc, bool isMatchPoint,
		bool opponentPredictedToSwitch = false); 

};