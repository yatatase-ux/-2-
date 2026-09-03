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

void ActionPhase::ProcessTurn()
{
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

	time--;

	if (turn == Earlyer)
	{
		if (time <= 0)
		{
			if (!turnOrder.isSwitchAction[Earlyer] && turnOrder.canAct[Earlyer] && turnOrder.willHit[Earlyer])
			{
				moveExecutor.Execute(turnOrder.mons[Earlyer], turnOrder.mons[Later], turnOrder.moveID[Earlyer]);
			}
			monsDying = aftermath.CheckFaint(turnOrder.mons[Later], context);
			time = 120;
			turn = Later;
		}
	}
	else // turn == Later
	{
		if (time <= 0)
		{
			if (!turnOrder.isSwitchAction[Later] && turnOrder.canAct[Later] && turnOrder.willHit[Later])
			{
				moveExecutor.Execute(turnOrder.mons[Later], turnOrder.mons[Earlyer], turnOrder.moveID[Later]);
			}
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
}