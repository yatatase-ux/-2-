#include "CpuAttackScorer.h"

/// <summary>
/// 技のスコアを評価
/// </summary>
/// <param name="moveID">技のID</param>
/// <param name="self">技を使う側(CPU)</param>
/// <param name="opponent">技を受ける側(プレイヤー)</param>
/// <param name="damageCalc">ダメージ計算機の参照</param>
/// <returns>計算されたスコア（期待ダメージを整数化した値）。補助技の場合は0を返す。</returns>
int CpuAttackScorer::Score(int moveID, const CpuEvalContext& ctx)
{
	const MoveData& move = MoveTable[moveID];

	int damage = ctx.damageCalc.CalcDamage(ctx.self, ctx.opponent, moveID);
	// 命中率を加味した期待値(まだ命中判定自体は未実装なので係数として使うだけ)
	float expected = damage * (move.Accuracy / 100.0f);
	float score = expected;

	// 撃破ボーナス
	if (damage >= ctx.opponent.CurrentHP)
	{
		// 相手が最後の一体なら更に加点
		score += ctx.isMatchPoint ? 150.0f : 80.0f;
	}

	// 先制技ボーナス
	if (move.Priority > 0)
	{
		bool isLethalByThisMove = (damage >= ctx.opponent.CurrentHP); // 条件A(先制技で倒せる場合)
		bool possiblyGoesSecond = (effect.GetEffectiveSpeed(ctx.self) <= effect.GetEffectiveSpeed(ctx.opponent)); // 後攻かどうか
		bool willDieFirst = possiblyGoesSecond && (riskEvaluator.EstimateKORisk(ctx.self, ctx.opponent, ctx.damageCalc) > 0.0f); // 条件B(相手より遅いかつ倒される)

		// 条件Aまたは条件Bを満たす場合、スコアにボーナスを加算
		if (isLethalByThisMove || willDieFirst)
		{
			score += 50.0f;
		}
	}

	float benchBonus = BenchConsistencyScore(move, ctx.opponent, ctx.opponentMembers, ctx.damageCalc);
	if (ctx.opponentPredictedToSwitch)
	{
		benchBonus *= 4.0f; // 相手が交代してくると読んでいるなら、通り技の価値を引き上げる
	}
	score += benchBonus;

	return (int)score;
}

/// <summary>
/// 控え一貫性
/// </summary>
/// <param name="move"></param>
/// <param name="enemyBox"></param>
/// <returns></returns>
float CpuAttackScorer::BenchConsistencyScore(const MoveData& move, BattleMonster& activeOpponent,
	Members& opponentMembers, DamageCalculator& damageCalc)
{
	int hitCount = 0;
	int checked = 0;

	for (int i = 0; i < MEMBER_MAX; i++)
	{
		BattleMonster* candidate = opponentMembers.mons[i];
		if (candidate == &activeOpponent) continue;				// 場に出ている本人は対象外
		if (!candidate->isRevealed) continue;					// まだ見せていない相手は対象外(いないものとして扱う)

		checked++;
		float matchup = damageCalc.TypeMatchup(*candidate->data, move);
		if (matchup >= 1.0f) hitCount++;
	}

	if (checked == 0) return 0.0f;								// 判断材料が無ければボーナスなし
	return (float)hitCount / checked * 5.0f;
}