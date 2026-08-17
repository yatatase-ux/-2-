#include "CpuBrain.h"
#include "MoveData.h"

int CpuBrain::ScoreMove(int moveID, BattleMonster& self, BattleMonster& opponent,
	DamageCalculator& damageCalc, EffectApplier& effect, bool isMatchPoint)
{
	const MoveData& move = MoveTable[moveID];
	return (move.category == MoveCategory::Status)
		? statusScorer.Score(moveID, self, opponent, damageCalc, effect)
		: attackScorer.Score(moveID, self, opponent, damageCalc, isMatchPoint);
}


int CpuBrain::ChooseMove(BattleMonster& self, BattleMonster& opponent,
	DamageCalculator& damageCalc, EffectApplier& effect, bool isMatchPoint)
{
	int bestMoveID = -1;
	int bestScore = -1;

	for (int i = 0; i < MOVE_SLOT_MAX; i++)
	{
		int moveID = self.data->MoveID[i];
		if (moveID < 0) continue;

		int score = ScoreMove(moveID, self, opponent, damageCalc, effect, isMatchPoint); // ‚±‚±‚ÅScoreMove‚ðÄ—˜—p
		if (score > bestScore)
		{
			bestScore = score;
			bestMoveID = moveID;
		}
	}
	return bestMoveID;
}