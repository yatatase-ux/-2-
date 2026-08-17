#include "CpuStatusScorer.h"
#include "MoveData.h"

int CpuStatusScorer::Score(int moveID, BattleMonster& self, BattleMonster& opponent,
	DamageCalculator& damageCalc, EffectApplier& effect)
{
	const MoveData& move = MoveTable[moveID];

	// ¡‰ñ‚Íƒ‰ƒ“ƒN•Ï“®‹Z‚Ì‚İ‘ÎÛBó‘ÔˆÙí•t—^‹Z‚ÍŒp‘±Œø‰Ê‚ª–¢À‘•‚Ì‚½‚ß0“_
	if (move.effect != EffectType::StatUp && move.effect != EffectType::StatDown)
	{
		return 0;
	}

	BattleMonster* target = move.targetSelf ? &self : &opponent;
	int currentRank = effect.GetRank(*target, move.statIndex);
	float score = 0.0f;

	if (move.statIndex == StatType::Speed)
	{
		float selfSpeedBefore = effect.GetEffectiveSpeed(self);
		float opponentSpeed = effect.GetEffectiveSpeed(opponent);
		float selfSpeedAfter = self.data->SPD * effect.RankToMultiplier(currentRank + move.statChange);

		bool wasSlowerOrEqual = (selfSpeedBefore <= opponentSpeed);
		bool willBeFaster = (selfSpeedAfter > opponentSpeed);

		if (wasSlowerOrEqual && willBeFaster)
		{
			score += 70.0f;
		}
	}
	else
	{
		// ‡@Ï‚İŒã‚Ì‰ü‘P—Ê + ‡Dƒ‰ƒ“ƒN“ª‘Å‚¿‚É‚æ‚éŒ¸Š
		float multiplier = effect.RankToMultiplier(currentRank + move.statChange);
		float raw = multiplier * 30.0f;

		int capRoom = (move.statChange > 0) ? (6 - currentRank) : (6 + currentRank);
		float damping = capRoom / 6.0f;
		if (damping < 0.0f) damping = 0.0f;
		if (damping > 1.0f) damping = 1.0f;

		score += raw * damping;
	}

	// ‡BÏ‚ñ‚¾ƒ^[ƒ“‚É“|‚³‚ê‚È‚¢‚©
	float risk = riskEvaluator.EstimateKORisk(self, opponent, damageCalc);
	score += (risk > 0.0f) ? (-300.0f * risk) : 10.0f;

	// ‡CŠù‚É“|‚¹‚éó‹µ‚Å‚Í‚È‚¢‚©
	int bestCurrentDamage = 0;
	for (int i = 0; i < MOVE_SLOT_MAX; i++)
	{
		int mID = self.data->MoveID[i];
		if (mID < 0) continue;
		const MoveData& mv = MoveTable[mID];
		if (mv.category == MoveCategory::Status) continue;

		int dmg = damageCalc.CalcDamage(self, opponent, mID);
		if (dmg > bestCurrentDamage) bestCurrentDamage = dmg;
	}
	bool canAlreadyKO = (bestCurrentDamage >= opponent.CurrentHP);
	score += canAlreadyKO ? -100.0f : 10.0f;

	return (int)score;
}