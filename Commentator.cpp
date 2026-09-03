#include "Commentator.h"
#include "CommentaryData.h"
#include "MoveData.h"
#include "DxLib.h"
#include <cstdio>

CommentarySituation Commentator::ClassifyReasoning(const CpuDecisionResult& decision, const CpuDecisionResult& predicted,
	BattleMonster& enemyBeforeSwitch, Members& pMembers,
	DamageCalculator& damageCalc, char* lineBuffer, int bufferSize)
{
	lineBuffer[0] = '\0';

	if (decision.switchToIndex < 0 && predicted.switchToIndex >= 0)
	{
		static const char* templates[] = {
			"%sへの交代を読んで%sを撃った！",
			"交代を予測、%sを見据えて%sで迎え撃つ！",
			"%sへの入れ替えを読み切り、%sで応戦！"
		};
		BattleMonster* predictedTarget = pMembers.mons[predicted.switchToIndex];
		sprintf_s(lineBuffer, bufferSize, templates[GetRand(2)],
			predictedTarget->data->Name, MoveTable[decision.selectedMoveID].Name);
		return CommentarySituation::StayReadingSwitch;
	}

	if (decision.switchToIndex >= 0 && predicted.switchToIndex < 0 && predicted.selectedMoveID >= 0)
	{
		float matchup = damageCalc.TypeMatchup(*enemyBeforeSwitch.data, MoveTable[predicted.selectedMoveID]);
		if (matchup >= 2.0f)
		{
			static const char* lines[] = {
				"相性不利と見て交代を選択！",
				"危険を察知し、素早く入れ替えた！",
				"このままでは分が悪いと判断、交代！"
			};
			sprintf_s(lineBuffer, bufferSize, "%s", lines[GetRand(2)]);
			return CommentarySituation::SwitchAvoidingThreat;
		}
	}

	return CommentarySituation::None;
}

bool Commentator::CheckHit(CommentarySituation reasoning, const CpuDecisionResult& predicted,
	bool playerActuallySwitched, int playerActualMoveID)
{
	if (reasoning == CommentarySituation::StayReadingSwitch)
	{
		bool predictedSwitch = (predicted.switchToIndex >= 0);
		return (playerActuallySwitched == predictedSwitch);
	}
	if (reasoning == CommentarySituation::SwitchAvoidingThreat)
	{
		return (!playerActuallySwitched && playerActualMoveID == predicted.selectedMoveID);
	}
	return false;
}

const char* Commentator::PickFollowUpLine(CommentarySituation reasoning, bool hit, bool cpuIsEarlyer)
{
	const char* candidates[16];
	int count = 0;

	for (int i = 0; i < CommentaryLineCount; i++)
	{
		const CommentaryLineEntry& entry = CommentaryLines[i];
		if (entry.situation == reasoning && entry.cpuIsEarlyer == cpuIsEarlyer && entry.hit == hit)
		{
			if (count < 16) candidates[count++] = entry.text;
		}
	}

	if (count == 0) return nullptr;
	return candidates[GetRand(count - 1)];
}

bool Commentator::CheckLastStand(BattleMonster& self, BattleMonster& opponent, int moveID, DamageCalculator& damageCalc)
{
	const MoveData& move = MoveTable[moveID];
	if (move.category == MoveCategory::Status || move.Priority <= 0) return false;

	int damage = damageCalc.CalcDamage(self, opponent, moveID);
	if (damage >= opponent.CurrentHP) return false; // 倒せるなら「最後のあがき」ではない

	bool possiblyGoesSecond = (effect.GetEffectiveSpeed(self) <= effect.GetEffectiveSpeed(opponent));
	return possiblyGoesSecond && (riskEvaluator.EstimateKORisk(self, opponent, damageCalc) > 0.0f);
}

const char* Commentator::PickLastStandLine()
{
	const char* candidates[] = {
		"この怪獣はお役御免か、先制技で少しでもダメージを与えます！",
		"もはや形勢は決している。それでも、最後まで抗う姿勢を見せた！",
		"生き残る道はない…それでも、意地の先制攻撃だ！"
	};
	return candidates[GetRand(2)];
}