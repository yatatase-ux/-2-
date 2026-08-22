#include "CpuStatusScorer.h"
#include "MoveData.h"

int CpuStatusScorer::CalcBestDamage(BattleMonster& attacker, BattleMonster& defender, DamageCalculator& damageCalc)
{
	int best = 0;
	for (int i = 0; i < MOVE_SLOT_MAX; i++)
	{
		int mID = attacker.data->MoveID[i];
		if (mID < 0) continue;
		const MoveData& mv = MoveTable[mID];
		if (mv.category == MoveCategory::Status) continue;

		int dmg = damageCalc.CalcDamage(attacker, defender, mID);
		if (dmg > best) best = dmg;
	}
	return best;
}

int CpuStatusScorer::Score(int moveID, BattleMonster& self, BattleMonster& opponent,
	DamageCalculator& damageCalc, EffectApplier& effect)
{
	const MoveData& move = MoveTable[moveID];	// ‹Zƒf[ƒ^‚Ìæ“¾

	if (move.effect != EffectType::StatUp && move.effect != EffectType::StatDown)
	{
		return 0;
	}

	BattleMonster* target = move.targetSelf ? &self : &opponent;	// ‘ÎÛw’è
	float score = 0.0f;		// ƒXƒRƒA‚Ì‰Šú‰»

	int bestCurrentDamage = CalcBestDamage(self, opponent, damageCalc); // ‡C‚Å‚àg‚¤

	int* rankPtr = effect.GetRankPtr(*target, move.statIndex);		// ”\—Íƒ‰ƒ“ƒN‚Ìƒ|ƒCƒ“ƒ^‚ğæ“¾ <- g‚¤Û‚Í•K‚¸•œŒ³‚ğ–Y‚ê‚È‚¢‚æ‚¤‚É‚·‚é
	int originalRank = *rankPtr;			// Œ³‚Ìƒ‰ƒ“ƒN‚ğ•Û‘¶

	if (move.statIndex == StatType::Speed)
	{
		// ‡A‘¬‚³ŠÖŒW‚Ì‹t“]
		float selfSpeedBefore = effect.GetEffectiveSpeed(self);
		float opponentSpeedBefore = effect.GetEffectiveSpeed(opponent);

		*rankPtr += move.statChange;
		if (*rankPtr > 6) *rankPtr = 6;
		if (*rankPtr < -6) *rankPtr = -6;

		float selfSpeedAfter = effect.GetEffectiveSpeed(self);
		float opponentSpeedAfter = effect.GetEffectiveSpeed(opponent);

		*rankPtr = originalRank; // •œŒ³ <- •K‚¸•œŒ³‚ğ–Y‚ê‚È‚¢‚æ‚¤‚É‚·‚é

		bool wasSlowerOrEqual = (selfSpeedBefore <= opponentSpeedBefore);
		bool willBeFaster = (selfSpeedAfter > opponentSpeedAfter);

		if (wasSlowerOrEqual && willBeFaster)
		{
			score += 70.0f;
		}
	}
	else
	{
		float incomingBefore = riskEvaluator.EstimateBestExpectedDamage(opponent, self, damageCalc);

		*rankPtr += move.statChange;
		if (*rankPtr > 6) *rankPtr = 6;
		if (*rankPtr < -6) *rankPtr = -6;

		int damageAfter = CalcBestDamage(self, opponent, damageCalc);
		float incomingAfter = riskEvaluator.EstimateBestExpectedDamage(opponent, self, damageCalc);

		*rankPtr = originalRank; // •œŒ³ <- •K‚¸•œŒ³‚ğ–Y‚ê‚È‚¢‚æ‚¤‚É‚·‚é

		float offenseGain = (float)(damageAfter - bestCurrentDamage); // —^ƒ_ƒ‚ª‘‚¦‚½•ª
		float defenseGain = incomingBefore - incomingAfter;           // ”íƒ_ƒ‚ªŒ¸‚Á‚½•ª

		score += offenseGain + defenseGain; // ’Êí‚Í‚Ç‚¿‚ç‚©•Ğ•û‚¾‚¯‚ª“®‚­‚Í‚¸
	}

	// ‡BÏ‚ñ‚¾ƒ^[ƒ“‚É“|‚³‚ê‚È‚¢‚©
	float risk = riskEvaluator.EstimateKORisk(self, opponent, damageCalc);
	score += (risk > 0.0f) ? (-300.0f * risk) : 10.0f;

	// ‡CŠù‚É“|‚¹‚éó‹µ‚Å‚Í‚È‚¢‚©
	bool canAlreadyKO = (bestCurrentDamage >= opponent.CurrentHP);
	score += canAlreadyKO ? -100.0f : 10.0f;

	return (int)score;
}