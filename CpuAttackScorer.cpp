#include "CpuAttackScorer.h"

/// <summary>
/// 技のスコアを評価
/// </summary>
/// <param name="moveID">技のID</param>
/// <param name="self">技を使う側(CPU)</param>
/// <param name="opponent">技を受ける側(プレイヤー)</param>
/// <param name="damageCalc">ダメージ計算機の参照</param>
/// <returns>計算されたスコア（期待ダメージを整数化した値）。補助技の場合は0を返す。</returns>
int CpuAttackScorer::Score(int moveID, BattleMonster& self, BattleMonster& opponent, DamageCalculator& damageCalc, bool isMatchPoint)
{
	const MoveData& move = MoveTable[moveID];

	if (move.category == MoveCategory::Status)
	{
		return 0; // 第一段階では補助技は評価しない(選ばれなくてOK)
	}

	int damage = damageCalc.CalcDamage(self, opponent, moveID);
	// 命中率を加味した期待値(まだ命中判定自体は未実装なので係数として使うだけ)
	float expected = damage * (move.Accuracy / 100.0f);
	float score = expected;

	// 撃破ボーナス
	if (damage >= opponent.CurrentHP)
	{
		score += isMatchPoint ? 150.0f : 80.0f;
	}

	// 先制技ボーナス
	if (move.Priority > 0)
	{
		bool isLethalByThisMove = (damage >= opponent.CurrentHP); // 条件A(先制技で倒せる場合)
		bool possiblyGoesSecond = (effect.GetEffectiveSpeed(self) <= effect.GetEffectiveSpeed(opponent)); // 後攻かどうか
		bool willDieFirst = possiblyGoesSecond && (riskEvaluator.EstimateKORisk(self, opponent, damageCalc) > 0.0f); // 条件B(相手より遅いかつ倒される)

		// 条件Aまたは条件Bを満たす場合、スコアにボーナスを加算
		if (isLethalByThisMove || willDieFirst)
		{
			score += 50.0f;
		}
	}

	return (int)score;
}

///// <summary>
///// 控え一貫性
///// </summary>
///// <param name="move"></param>
///// <param name="enemyBox"></param>
///// <returns></returns>
//float CpuBrain::BenchConsistencyScore(const MoveData& move, const Members& enemyBox)
//{
//	int hitCount = 0;
//	int checked = 0;
//
//	for (int i = 0; i < PARTY_MAX; i++) // 相手が選んだ6体のうち
//	{
//		if (enemyBox.mons[i]->isRevealed) continue; // 既に場に出て見えている個体は除外(通常ダメージ側で評価済みのため)
//
//		checked++;
//		float matchup = damageCalc.TypeMatchup(*enemyBox.mons[i]->data, move);
//		if (matchup >= 1.0f) hitCount++; // 等倍以上なら「効く」とみなす
//	}
//
//	if (checked == 0) return 0.0f;
//	return (float)hitCount / checked * 5.0f; // 最大+5、効く割合に応じて按分
//}