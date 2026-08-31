#include "CpuSwitchScorer.h"

int CpuSwitchScorer::Score(const CpuEvalContext& ctx, BattleMonster& candidate)
{
	float score = 0.0f;

	// ‡@”Õ–Ê‰ü‘P—Ê:—^ƒ_ƒ(Œó•â‚ªo‚½ê‡‚Ì•û‚ª‚Ç‚ê‚¾‚¯—Ç‚­‚È‚é‚©)
	float selfOutgoing = riskEvaluator.EstimateBestExpectedDamage(ctx.self, ctx.opponent, ctx.damageCalc);
	float candidateOutgoing = riskEvaluator.EstimateBestExpectedDamage(candidate, ctx.opponent, ctx.damageCalc);
	score += (candidateOutgoing - selfOutgoing);

	// ‡@”Õ–Ê‰ü‘P—Ê:”íƒ_ƒ
	float selfIncoming = riskEvaluator.EstimateBestExpectedDamage(ctx.opponent, ctx.self, ctx.damageCalc);
	float candidateIncoming = riskEvaluator.EstimateBestExpectedDamage(ctx.opponent, candidate, ctx.damageCalc);
	score += (selfIncoming - candidateIncoming);

	// ‡@‘¬‚³ŠÖŒW‚Ì‹t“]
	float selfSpeed = effect.GetEffectiveSpeed(ctx.self);
	float candidateSpeed = effect.GetEffectiveSpeed(candidate);
	float opponentSpeed = effect.GetEffectiveSpeed(ctx.opponent);
	if (selfSpeed <= opponentSpeed && candidateSpeed > opponentSpeed)
	{
		score += 70.0f;
	}

	// ‡BŒğ‘ãæ‚Ìó‚¯–ÊŠëŒ¯“x(Œğ‘ãæ©g‚ª‘¦À‚É“|‚³‚ê‚éŠëŒ¯‚ª‚È‚¢‚©)
	float candidateRisk = riskEvaluator.EstimateKORisk(candidate, ctx.opponent, ctx.damageCalc);
	score += (candidateRisk > 0.0f) ? (-300.0f * candidateRisk) : 0.0f;

	return (int)score;
}