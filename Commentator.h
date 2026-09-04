#pragma once
#include "CommentarySituation.h"
#include "BattleMonster.h"
#include "DamageCalculator.h"
#include "Party.h"
#include "CpuDebugTypes.h" // CpuDecisionResult‚Ì’è‹`
#include "CpuRiskEvaluator.h"
#include "EffectApplier.h"

class Commentator
{
private:
	CpuRiskEvaluator riskEvaluator; // 
	EffectApplier effect;           //

public:
	CommentarySituation ClassifyReasoning(const CpuDecisionResult& decision, const CpuDecisionResult& predicted,
		BattleMonster& enemyBeforeSwitch, Members& pMembers, Members& eMembers,
		DamageCalculator& damageCalc, char* lineBuffer, int bufferSize);

	bool CheckHit(CommentarySituation reasoning, const CpuDecisionResult& predicted,
		bool playerActuallySwitched, int playerActualMoveID);

	const char* PickFollowUpLine(CommentarySituation reasoning, bool hit, bool cpuIsEarlyer);

	bool CheckLastStand(BattleMonster& self, BattleMonster& opponent, int moveID, DamageCalculator& damageCalc);
	const char* PickLastStandLine();
};