#include "ActionPhase.h"

PHASE_CONSTRUCTOR(ActionPhase)
{
	turnOrder = turnOrderResolver.Resolve(context, pMembers, eMembers);

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
		presenter.DrawTurnPreview(turn, turnOrder, moveExecutor);
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
			if (!turnOrder.isSwitchAction[Earlyer] && turnOrder.canAct[Earlyer])
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
			if (!turnOrder.isSwitchAction[Later] && turnOrder.canAct[Later])
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