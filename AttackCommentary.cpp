#include "AttackCommentary.h"
#include "MoveData.h"

CommentarySituation AttackCommentary::Classify(BattleMonster& self, BattleMonster& opponent, int moveID,
	DamageCalculator& damageCalc, bool isMatchPoint)
{
	const MoveData& move = MoveTable[moveID];

	int damage = damageCalc.CalcDamage(self, opponent, moveID);
	bool isLethal = (damage >= opponent.CurrentHP);

	if (isLethal && isMatchPoint) return CommentarySituation::MatchPointKO;
	if (isLethal && move.Priority > 0) return CommentarySituation::PriorityKill;
	if (isLethal) return CommentarySituation::NormalKO;

	if (move.Priority > 0)
	{
		bool possiblyGoesSecond = (effect.GetEffectiveSpeed(self) <= effect.GetEffectiveSpeed(opponent));
		bool willDieFirst = possiblyGoesSecond && (riskEvaluator.EstimateKORisk(self, opponent, damageCalc) > 0.0f);
		if (willDieFirst) return CommentarySituation::PriorityEscape;
	}

	float matchup = damageCalc.TypeMatchup(*opponent.data, move);
	if (matchup >= 2.0f) return CommentarySituation::SuperEffective;
	if (matchup <= 0.5f) return CommentarySituation::NotVeryEffective;

	return CommentarySituation::None;
}