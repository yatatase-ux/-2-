#include "CpuSwitchScorer.h"

int CpuSwitchScorer::Score(const CpuEvalContext& ctx, BattleMonster& candidate)
{
	float score = 0.0f;

	// ①盤面改善量:与ダメ(候補が出た場合の方がどれだけ良くなるか)
	float selfOutgoing = riskEvaluator.EstimateBestExpectedDamage(ctx.self, ctx.opponent, ctx.damageCalc);
	float candidateOutgoing = riskEvaluator.EstimateBestExpectedDamage(candidate, ctx.opponent, ctx.damageCalc);
	score += (candidateOutgoing - selfOutgoing);

	// ①盤面改善量:被ダメ
	float selfIncoming = riskEvaluator.EstimateBestExpectedDamage(ctx.opponent, ctx.self, ctx.damageCalc);
	float candidateIncoming = riskEvaluator.EstimateBestExpectedDamage(ctx.opponent, candidate, ctx.damageCalc);
	score += (selfIncoming - candidateIncoming);

	// ①速さ関係の逆転
	float selfSpeed = effect.GetEffectiveSpeed(ctx.self);
	float candidateSpeed = effect.GetEffectiveSpeed(candidate);
	float opponentSpeed = effect.GetEffectiveSpeed(ctx.opponent);
	if (selfSpeed <= opponentSpeed && candidateSpeed > opponentSpeed)
	{
		score += 70.0f;
	}

	// ③交代先の受け面危険度(交代先自身が即座に倒される危険がないか)
	float candidateRisk = riskEvaluator.EstimateKORisk(candidate, ctx.opponent, ctx.damageCalc);
	score += (candidateRisk > 0.0f) ? (-300.0f * candidateRisk) : 0.0f;

	// ④予測される「次の対峙相手」に対する安全性
	if (ctx.predictedOpponentDecision != nullptr)
	{
		// 相手の行動予測がある場合、交代先候補がその行動に対してどれだけ安全かを評価する
		if (ctx.predictedOpponentDecision->switchToIndex >= 0)
		{
			// パターンA:相手も交代してくると予想される場合、その交代先候補との相性を見る
			BattleMonster* predictedIncoming = ctx.opponentMembers.mons[ctx.predictedOpponentDecision->switchToIndex];	// 相手の交代先候補
			float riskAgainstPredicted = riskEvaluator.EstimateKORisk(candidate, *predictedIncoming, ctx.damageCalc);	// 交代先候補が相手の交代先候補に対してどれだけ危険か
			score += (riskAgainstPredicted > 0.0f) ? (-300.0f * riskAgainstPredicted) : 20.0f;							// 危険がなければ少し加点
		}
		// 相手の行動予測が技を撃ってくる場合、その技を受けた後の状態を見る
		else if (ctx.predictedOpponentDecision->selectedMoveID >= 0)
		{
			// パターンB:相手が技を撃ってくると予想される場合、その技を受けた後の状態を見る
			int predictedDamage = ctx.damageCalc.CalcDamage(ctx.opponent, candidate, ctx.predictedOpponentDecision->selectedMoveID);	// 交代先候補が受けると予想されるダメージ量
			float remainingRatio = (float)(candidate.CurrentHP - predictedDamage) / candidate.data->HP;									// 交代先候補が受けると予想されるダメージ量に対する残りHP比率

			if (remainingRatio <= 0.0f) score -= 300.0f;      // 瀕死になるなら大きく減点
			else if (remainingRatio < 0.3f) score -= 100.0f;  // 大きく削られるならそれなりに減点
			else score += 20.0f;                                // 大丈夫そうなら加点
		}
	}

	return (int)score;
}