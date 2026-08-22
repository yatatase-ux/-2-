#include "CpuSwitchScorer.h"

int CpuSwitchScorer::Score(BattleMonster& self, BattleMonster& opponent, BattleMonster& candidate, DamageCalculator& damageCalc)
{
	float score = 0.0f;

	// ‡@”Õ–Ê‰ü‘P—Ê:—^ƒ_ƒ(Œó•â‚ªo‚½ê‡‚Ì•û‚ª‚Ç‚ê‚¾‚¯—Ç‚­‚È‚é‚©)
	float selfOutgoing = riskEvaluator.EstimateBestExpectedDamage(self, opponent, damageCalc);
	float candidateOutgoing = riskEvaluator.EstimateBestExpectedDamage(candidate, opponent, damageCalc);
	score += (candidateOutgoing - selfOutgoing);

	// ‡@”Õ–Ê‰ü‘P—Ê:”íƒ_ƒ
	float selfIncoming = riskEvaluator.EstimateBestExpectedDamage(opponent, self, damageCalc);
	float candidateIncoming = riskEvaluator.EstimateBestExpectedDamage(opponent, candidate, damageCalc);
	score += (selfIncoming - candidateIncoming);

	// ‡@‘¬‚³ŠÖŒW‚Ì‹t“]
	float selfSpeed = effect.GetEffectiveSpeed(self);
	float candidateSpeed = effect.GetEffectiveSpeed(candidate);
	float opponentSpeed = effect.GetEffectiveSpeed(opponent);
	if (selfSpeed <= opponentSpeed && candidateSpeed > opponentSpeed)
	{
		score += 70.0f;
	}

	// ‡BŒğ‘ãæ‚Ìó‚¯–ÊŠëŒ¯“x(Œğ‘ãæ©g‚ª‘¦À‚É“|‚³‚ê‚éŠëŒ¯‚ª‚È‚¢‚©)
	float candidateRisk = riskEvaluator.EstimateKORisk(candidate, opponent, damageCalc);
	score += (candidateRisk > 0.0f) ? (-300.0f * candidateRisk) : 0.0f;

	return (int)score;
}