#include "CpuRiskEvaluator.h"

float CpuRiskEvaluator::EstimateKORisk(BattleMonster& self, BattleMonster& opponent, DamageCalculator& damageCalc)
{
	float worstRisk = 0.0f;
	for (int i = 0; i < MOVE_SLOT_MAX; i++)
	{
		int moveID = opponent.data->MoveID[i];
		if (moveID < 0) continue;

		float risk = damageCalc.LethalProbability(opponent, self, moveID);
		if (risk > worstRisk) worstRisk = risk;
	}
	return worstRisk;
}