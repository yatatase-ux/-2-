#include "CpuBrain.h"
#include "MoveData.h"

int CpuBrain::ScoreMove(int moveID, BattleMonster& self, BattleMonster& opponent,
	Members& opponentMembers, DamageCalculator& damageCalc, bool isMatchPoint)
{
	const MoveData& move = MoveTable[moveID];
	return (move.category == MoveCategory::Status)
		? statusScorer.Score(moveID, self, opponent, damageCalc, effect)
		: attackScorer.Score(moveID, self, opponent, opponentMembers, damageCalc, isMatchPoint);
}

CpuDecisionResult CpuBrain::Decide(BattleMonster& self, BattleMonster& opponent, Members& selfMembers,
	Members& opponentMembers, DamageCalculator& damageCalc, bool isMatchPoint)
{
	CpuDecisionResult result;

	// 技のスコアを全部計算
	int bestMoveScore = -100000;
	int bestMoveID = -1;
	for (int i = 0; i < MOVE_SLOT_MAX; i++)
	{
		int moveID = self.data->MoveID[i];
		if (moveID < 0) { result.moveScores[i] = { -1, 0 }; continue; }

		int score = ScoreMove(moveID, self, opponent, opponentMembers, damageCalc, isMatchPoint);
		result.moveScores[i] = { moveID, score };
		if (score > bestMoveScore) { bestMoveScore = score; bestMoveID = moveID; }
	}

	// 控えの交代候補スコアを全部計算(場に出ている本人・瀕死個体は除外)
	int bestSwitchScore = -100000;
	int bestSwitchIndex = -1;
	int debugIdx = 0;
	for (int i = 0; i < MEMBER_MAX; i++)
	{
		BattleMonster* candidate = selfMembers.mons[i];
		if (candidate == &self || candidate->isFainted) continue;

		int score = switchScorer.Score(self, opponent, *candidate, damageCalc);
		if (debugIdx < MEMBER_MAX - 1) result.switchScores[debugIdx] = { candidate->data->Name, score };
		debugIdx++;

		if (score > bestSwitchScore) { bestSwitchScore = score; bestSwitchIndex = i; }
	}

	// 技 vs 交代、最終比較
	if (bestSwitchIndex >= 0 && bestSwitchScore > bestMoveScore)
	{
		result.switchToIndex = bestSwitchIndex;
	}
	else
	{
		result.selectedMoveID = bestMoveID;
	}

	return result;
}