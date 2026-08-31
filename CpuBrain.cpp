#include "CpuBrain.h"
#include "MoveData.h"

int CpuBrain::ScoreMove(int moveID, const CpuEvalContext& ctx)
{
	const MoveData& move = MoveTable[moveID];

	return (move.category == MoveCategory::Status)
		? statusScorer.Score(moveID, ctx)
		: attackScorer.Score(moveID, ctx);
}

CpuDecisionResult CpuBrain::Decide(CpuEvalContext ctx, bool checkOscillation)
{
	CpuDecisionResult result;

	// 技のスコアを全部計算
	int bestMoveScore = -100000;
	int bestMoveID = -1;
	for (int i = 0; i < MOVE_SLOT_MAX; i++)
	{
		int moveID = ctx.self.data->MoveID[i];
		if (moveID < 0) { result.moveScores[i] = { -1, 0 }; continue; }

		int score = ScoreMove(moveID, ctx);
		result.moveScores[i] = { moveID, score };
		if (score > bestMoveScore) { bestMoveScore = score; bestMoveID = moveID; }
	}

	// 控えの交代候補スコアを全部計算(場に出ている本人・瀕死個体は除外)
	int bestSwitchScore = -100000;
	int bestSwitchIndex = -1;
	int debugIdx = 0;
	for (int i = 0; i < MEMBER_MAX; i++)
	{
		BattleMonster* candidate = ctx.selfMembers.mons[i];
		if (candidate == &ctx.self || candidate->isFainted) continue;

		int score = switchScorer.Score(ctx, *candidate);
		if (ctx.opponentPredictedToSwitch) score -= 100; // 相手も交代を読んでいるなら、こちらは居座った方が得

		if (debugIdx < MEMBER_MAX - 1) result.switchScores[debugIdx] = { candidate->data->Name, score };
		debugIdx++;

		if (score > bestSwitchScore) { bestSwitchScore = score; bestSwitchIndex = i; }
	}

	bool wantsToSwitch = (bestSwitchIndex >= 0 && bestSwitchScore > bestMoveScore);

	if (wantsToSwitch && checkOscillation)
	{
		BattleMonster* candidate = ctx.selfMembers.mons[bestSwitchIndex];

		// 交代先(candidate)を新しいselfとした、別のctxを作って評価する
		CpuEvalContext candidateCtx{ *candidate, ctx.opponent, ctx.selfMembers, ctx.opponentMembers, ctx.damageCalc, ctx.isMatchPoint };
		CpuDecisionResult candidateView = Decide(candidateCtx, false);

		if (candidateView.switchToIndex >= 0)
		{
			wantsToSwitch = false; // 交代先も交代したがっているなら、居座って技を選ぶ
		}
	}

	// 技 vs 交代、最終比較
	if (wantsToSwitch)
	{
		result.switchToIndex = bestSwitchIndex;
	}
	else
	{
		result.selectedMoveID = bestMoveID;
	}

	return result;
}