#pragma once
#include "BattleMonster.h"
#include "Party.h"
#include "DamageCalculator.h"
#include "CpuDebugTypes.h"

struct CpuEvalContext
{
	BattleMonster& self;
	BattleMonster& opponent;
	Members& selfMembers;
	Members& opponentMembers;
	DamageCalculator& damageCalc;
	bool isMatchPoint = false;
	bool opponentPredictedToSwitch = false;
	const CpuDecisionResult* predictedOpponentDecision = nullptr; // –¢ŒvŽZ/•s—v‚È‚çnullptr
};