#include "ActionPhase.h"
#include <cstdio>

PHASE_CONSTRUCTOR(ActionPhase)
{
	turnOrder = turnOrderResolver.Resolve(context, pMembers, eMembers);

	for (int slot = 0; slot < ActionMax; slot++)
	{
		reasoningOnlyLine[slot] = nullptr;
		followUpLine[slot] = nullptr;
		baseLineText[slot][0] = '\0';

		if (turnOrder.isSwitchAction[slot]) continue;
		if (!turnOrder.canAct[slot]) continue;
		if (!turnOrder.willHit[slot]) continue;

		BattleMonster* actor = turnOrder.mons[slot];
		int moveID = turnOrder.moveID[slot];
		sprintf_s(baseLineText[slot], "%sは%sを選択！", actor->data->Name, MoveTable[moveID].Name);
	}

	// 思考可視化(予測ベース)の表示振り分け
	if (context->cpuReasoning != CommentarySituation::None)
	{
		bool cpuIsEarlyer = (turnOrder.mons[Earlyer] == context->enemy);

		if (context->cpuReasoning == CommentarySituation::SwitchMatchingRead)
		{
			// この状況は答え合わせ不要:CPUのターンに理由をそのまま出すだけで完結する
			int cpuSlot = cpuIsEarlyer ? Earlyer : Later;
			reasoningOnlyLine[cpuSlot] = context->cpuReasoningLine;
		}
		else
		{
			// 既存のStayReadingSwitch/SwitchAvoidingThreat(2段階構成)は変更なし
			int playerSlot = cpuIsEarlyer ? Later : Earlyer;
			bool playerActuallySwitched = turnOrder.isSwitchAction[playerSlot];
			int playerActualMoveID = playerActuallySwitched ? -1 : turnOrder.moveID[playerSlot];

			bool hit = commentator.CheckHit(context->cpuReasoning, context->predictedPlayerDecision,
				playerActuallySwitched, playerActualMoveID);

			if (cpuIsEarlyer)
			{
				reasoningOnlyLine[Earlyer] = context->cpuReasoningLine;
			}
			followUpLine[Later] = commentator.PickFollowUpLine(context->cpuReasoning, hit, cpuIsEarlyer);
		}
	}

	time = 120;
	turn = Earlyer;
	turnEnd = false;
	monsDying = false;
	showingStatusResult = false;
}

PhaseState ActionPhase::Input()
{
	return PhaseState::NONE;
}

PhaseState ActionPhase::Update()
{
	ProcessTurn();
	if (monsDying) return PhaseState::CHECK_FAINT;
	if (turnEnd) return PhaseState::COMMAND;
	return PhaseState::NONE;
}

void ActionPhase::Draw()
{
	battleHUD.Draw(*context->player, *context->enemy);

	if (showingStatusResult)
	{
		if (statusTime > 0)
		{
			presenter.DrawStatusTick(statusResult);
		}
		return;
	}

	if (time > 0)
	{
		presenter.DrawTurnPreview(turn, turnOrder, moveExecutor,
			baseLineText[turn], reasoningOnlyLine[turn], followUpLine[turn]);
	}
}

void ActionPhase::Sound()
{
}

/// <summary>
/// ターン決定
/// </summary>
void ActionPhase::ProcessTurn()
{
	if (monsDying || turnEnd) return;

	if (showingStatusResult)
	{
		statusTime--;
		if (statusTime <= 0)
		{
			showingStatusResult = false;
			turnEnd = true;
		}
		return;
	}

	// ダメージ演出待ち:終わるまでは、今の実況(turnに対応するもの)を表示し続けたまま足踏みする
	if (waitingForHPAnim)
	{
		battleHUD.UpdateHPAnimation(*context->player);
		battleHUD.UpdateHPAnimation(*context->enemy);

		if (!battleHUD.IsHPAnimDone(*context->player) || !battleHUD.IsHPAnimDone(*context->enemy))
		{
			return; // まだアニメーション中
		}
		waitingForHPAnim = false;
		AdvanceAfterAction();
		return;
	}

	time--;

	if (turn == Earlyer)
	{
		if (time > 0) return;

		if (!turnOrder.isSwitchAction[Earlyer] && turnOrder.canAct[Earlyer] && turnOrder.willHit[Earlyer])
		{
			moveExecutor.Execute(turnOrder.mons[Earlyer], turnOrder.mons[Later], turnOrder.moveID[Earlyer]);
			waitingForHPAnim = true; // ダメージが発生したので、アニメーション待ちへ(turnはまだ切り替えない)
			return;
		}
		AdvanceAfterAction(); // 交代/まひ/外れの場合はダメージが無いので、そのまま進む
	}
	else // Later
	{
		if (time > 0) return;

		if (!turnOrder.isSwitchAction[Later] && turnOrder.canAct[Later] && turnOrder.willHit[Later])
		{
			moveExecutor.Execute(turnOrder.mons[Later], turnOrder.mons[Earlyer], turnOrder.moveID[Later]);
			waitingForHPAnim = true;
			return;
		}
		AdvanceAfterAction();
	}
}

// 瀕死判定・状態異常処理をまとめる(アニメーション待ちが終わった後、またはダメージが無かった場合に呼ばれる)
void ActionPhase::AdvanceAfterAction()
{
	if (turn == Earlyer)
	{
		monsDying = aftermath.CheckFaint(turnOrder.mons[Later], context);
		time = 120;
		turn = Later; // ここで初めてturnを進める
	}
	else
	{
		monsDying = aftermath.CheckFaint(turnOrder.mons[Earlyer], context);
		if (!monsDying)
		{
			statusResult = aftermath.ProcessEndOfTurn(turnOrder.mons, context);
			if (statusResult.causedFaint)
			{
				monsDying = true;
			}
			else if (statusResult.name[Earlyer] != nullptr || statusResult.name[Later] != nullptr)
			{
				showingStatusResult = true;
				statusTime = 60;
			}
			else
			{
				turnEnd = true;
			}
		}
	}
}