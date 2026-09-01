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

int CpuStatusScorer::Score(int moveID, const CpuEvalContext& ctx)
{
	const MoveData& move = MoveTable[moveID];	// ‹Zƒf[ƒ^‚Ìæ“¾

	if (move.effect != EffectType::StatUp && move.effect != EffectType::StatDown)
	{
		return 0;
	}

	BattleMonster* target = move.targetSelf ? &ctx.self : &ctx.opponent;	// ‘ÎÛw’è
	float score = 0.0f;		// ƒXƒRƒA‚Ì‰Šú‰»
	bool hasEffect = false;

	int bestCurrentDamage = CalcBestDamage(ctx.self, ctx.opponent, ctx.damageCalc); // ‡C‚Å‚àg‚¤

	int* rankPtr = effect.GetRankPtr(*target, move.statIndex);		// ”\—Íƒ‰ƒ“ƒN‚Ìƒ|ƒCƒ“ƒ^‚ğæ“¾ <- g‚¤Û‚Í•K‚¸•œŒ³‚ğ–Y‚ê‚È‚¢‚æ‚¤‚É‚·‚é
	int originalRank = *rankPtr;			// Œ³‚Ìƒ‰ƒ“ƒN‚ğ•Û‘¶

	if (move.statIndex == StatType::Speed)
	{
		// ‡A‘¬‚³ŠÖŒW‚Ì‹t“]
		float selfSpeedBefore = effect.GetEffectiveSpeed(ctx.self);
		float opponentSpeedBefore = effect.GetEffectiveSpeed(ctx.opponent);

		*rankPtr += move.statChange;
		if (*rankPtr > 6) *rankPtr = 6;
		if (*rankPtr < -6) *rankPtr = -6;

		float selfSpeedAfter = effect.GetEffectiveSpeed(ctx.self);
		float opponentSpeedAfter = effect.GetEffectiveSpeed(ctx.opponent);

		*rankPtr = originalRank; // •œŒ³ <- •K‚¸•œŒ³‚ğ–Y‚ê‚È‚¢‚æ‚¤‚É‚·‚é

		bool wasSlowerOrEqual = (selfSpeedBefore <= opponentSpeedBefore);
		bool willBeFaster = (selfSpeedAfter > opponentSpeedAfter);

		if (wasSlowerOrEqual && willBeFaster)
		{
			score += 70.0f;
			hasEffect = true;
		}
	}
	else
	{
		float incomingBefore = riskEvaluator.EstimateBestExpectedDamage(ctx.opponent, ctx.self, ctx.damageCalc);

		*rankPtr += move.statChange;
		if (*rankPtr > 6) *rankPtr = 6;
		if (*rankPtr < -6) *rankPtr = -6;

		int damageAfter = CalcBestDamage(ctx.self, ctx.opponent, ctx.damageCalc);
		float incomingAfter = riskEvaluator.EstimateBestExpectedDamage(ctx.opponent, ctx.self, ctx.damageCalc);

		*rankPtr = originalRank; // •œŒ³ <- •K‚¸•œŒ³‚ğ–Y‚ê‚È‚¢‚æ‚¤‚É‚·‚é

		float offenseGain = (float)(damageAfter - bestCurrentDamage); // —^ƒ_ƒ‚ª‘‚¦‚½•ª
		float defenseGain = incomingBefore - incomingAfter;           // ”íƒ_ƒ‚ªŒ¸‚Á‚½•ª
		float rawGain = offenseGain + defenseGain;

		score += rawGain; // ’Êí‚Í‚Ç‚¿‚ç‚©•Ğ•û‚¾‚¯‚ª“®‚­‚Í‚¸
		hasEffect = (rawGain > 0.0f);
	}

	// ‡BÏ‚ñ‚¾ƒ^[ƒ“‚É“|‚³‚ê‚È‚¢‚©
	float risk = riskEvaluator.EstimateKORisk(ctx.self, ctx.opponent, ctx.damageCalc);
	if (risk > 0.0f)
	{
		score += -300.0f * risk;
	}
	else if (hasEffect)
	{
		score += 10.0f;
	}

	// ‡CŠù‚É“|‚¹‚éó‹µ‚Å‚Í‚È‚¢‚©
	bool canAlreadyKO = (bestCurrentDamage >= ctx.opponent.CurrentHP);
	if (canAlreadyKO)
	{
		score += -100.0f;
	}
	else if (hasEffect)
	{
		score += 10.0f;
	}

	return (int)score;
}