#include "CpuBrain.h"

/// <summary>
/// 技のスコアを評価
/// </summary>
/// <param name="moveID">技のID</param>
/// <param name="self">技を使う側(CPU)</param>
/// <param name="opponent">技を受ける側(プレイヤー)</param>
/// <param name="damageCalc">ダメージ計算機の参照</param>
/// <returns>計算されたスコア（期待ダメージを整数化した値）。補助技の場合は0を返す。</returns>
int CpuBrain::ScoreMove(int moveID, BattleMonster& self, BattleMonster& opponent, DamageCalculator& damageCalc)
{
	const MoveData& move = MoveTable[moveID];

	if (move.category == MoveCategory::Status)
	{
		return 0; // 第一段階では補助技は評価しない(選ばれなくてOK)
	}

	int damage = damageCalc.CalcDamage(self, opponent, moveID);

	// 命中率を加味した期待値(まだ命中判定自体は未実装なので係数として使うだけ)
	float expected = damage * (move.Accuracy / 100.0f);

	return (int)expected;
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

/// <summary>
/// 戦闘不能リスク評価
/// </summary>
/// <param name="self"></param>
/// <param name="opponent"></param>
/// <param name="damageCalc"></param>
/// <returns></returns>
float CpuBrain::EstimateKORisk(BattleMonster& self, BattleMonster& opponent, DamageCalculator& damageCalc)
{
	float worstRisk = 0.0f;
	for (int i = 0; i < 4; i++)
	{
		int moveID = opponent.data->MoveID[i];
		if (moveID < 0) continue;

		float risk = damageCalc.LethalProbability(opponent, self, moveID);
		if (risk > worstRisk) worstRisk = risk;
	}
	return worstRisk;
}

/// <summary>
/// 評価したスコアをもとに最適な行動を選択
/// </summary>
/// <param name="self"></param>
/// <param name="opponent"></param>
/// <param name="damageCalc"></param>
/// <returns></returns>
int CpuBrain::ChooseMove(BattleMonster& self, BattleMonster& opponent, DamageCalculator& damageCalc)
{
	int bestMoveID = -1;
	int bestScore = -1;

	for (int i = 0; i < 4; i++)
	{
		int moveID = self.data->MoveID[i];
		if (moveID < 0) continue;
		int score = ScoreMove(moveID, self, opponent, damageCalc);

		lastScores[i] = { moveID, score };

		if (score > bestScore)
		{
			bestScore = score;
			bestMoveID = moveID;
		}
	}
	return bestMoveID;
}

MoveScoreDebug* CpuBrain::GetLastScore(int num)
{
	return &lastScores[num];
}
