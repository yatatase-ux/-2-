#include "StatusCommentary.h"
#include "MoveData.h"

CommentarySituation StatusCommentary::Classify(BattleMonster& self, BattleMonster& opponent, int moveID, DamageCalculator& damageCalc)
{
	const MoveData& move = MoveTable[moveID];

	if (move.effect == EffectType::Poison || move.effect == EffectType::Burn)
	{
		return CommentarySituation::InflictStatusDamage;
	}
	if (move.effect == EffectType::Paralysis)
	{
		return CommentarySituation::InflictParalysis;
	}
	if (move.effect == EffectType::StatDown && !move.targetSelf)
	{
		return CommentarySituation::Debuff;
	}
	if (move.effect == EffectType::StatUp && move.targetSelf)
	{
		float risk = riskEvaluator.EstimateKORisk(self, opponent, damageCalc);
		if (risk > 0.0f) return CommentarySituation::RiskyBoost;

		if (move.statIndex == StatType::Speed) return CommentarySituation::BoostSpeed;
		if (move.statIndex == StatType::PhysicalAtk || move.statIndex == StatType::MagicAtk)
			return CommentarySituation::BoostOffense;
		if (move.statIndex == StatType::PhysicalDef || move.statIndex == StatType::MagicDef)
			return CommentarySituation::BoostDefense;
	}

	return CommentarySituation::None;
}