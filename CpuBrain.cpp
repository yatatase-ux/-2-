#include "CpuBrain.h"

int CpuBrain::ChooseMove(BattleMonster& self, BattleMonster& opponent,
	DamageCalculator& damageCalc, EffectApplier& effect, bool isMatchPoint)
{
	int bestMoveID = -1;
	int bestScore = -1;

	for (int i = 0; i < 4; i++)
	{
		int moveID = self.data->MoveID[i];
		if (moveID < 0) continue;

		const MoveData& move = MoveTable[moveID];
		int score = (move.category == MoveCategory::Status)
			? statusScorer.Score(moveID, self, opponent, damageCalc, effect)
			: attackScorer.Score(moveID, self, opponent, damageCalc, isMatchPoint);

		if (score > bestScore)
		{
			bestScore = score;
			bestMoveID = moveID;
		}
	}
	return bestMoveID;
}