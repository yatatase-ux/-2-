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

float CpuRiskEvaluator::EstimateBestExpectedDamage(BattleMonster& attacker, BattleMonster& defender, DamageCalculator& damageCalc)
{
	float best = 0.0f;
	for (int i = 0; i < MOVE_SLOT_MAX; i++)
	{
		int moveID = attacker.data->MoveID[i];
		if (moveID < 0) continue;
		const MoveData& move = MoveTable[moveID];
		if (move.category == MoveCategory::Status) continue;

		int dmg = damageCalc.CalcDamage(attacker, defender, moveID);
		float expected = dmg * (move.Accuracy / 100.0f);
		if (expected > best) best = expected;
	}
	return best;
}