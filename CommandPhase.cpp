#include "CommandPhase.h"
#include "MonsterBaseData.h"

PHASE_CONSTRUCTOR(CommandPhase)
{
	button[Fight] = { 1150.0f, 425.0f, 75.0f, GetColor(175,0,0) };
	button[Change] = { 1150.0f, 600.0f, 75.0f, GetColor(0,175,0) };
	context->player->selectedMoveID = -1;

	int aliveCount = 0;
	for (int i = 0; i < MEMBER_MAX; i++)
		if (!pMembers->mons[i]->isFainted) aliveCount++;
	bool isMatchPoint = (aliveCount <= 1);

	CpuDecisionResult decision = cpuBrain.Decide(*context->enemy, *context->player, *eMembers, *pMembers, damage, isMatchPoint);

	for (int i = 0; i < MOVE_SLOT_MAX; i++) context->enemyMoveScore[i] = decision.moveScores[i];
	for (int i = 0; i < MEMBER_MAX - 1; i++) context->enemySwitchScore[i] = decision.switchScores[i];

	if (decision.switchToIndex >= 0)
	{
		context->enemy->changeMonster = decision.switchToIndex;
		context->enemy->selectedMoveID = -1;
	}
	else
	{
		context->enemy->selectedMoveID = decision.selectedMoveID;
		context->enemy->changeMonster = -1;
	}

	context->player->changeMonster = -1;
}

/// <summary>
/// “ü—Íˆ—
/// </summary>
PhaseState CommandPhase::Input()
{
	bool click = input->Mouse().Push(MOUSE_LEFT);

	if (click)
	{
		if (CursorInButton(Fight))
			return PhaseState::MOVE_SELECT;

		if (CursorInButton(Change))
			return PhaseState::CHANGE_MONS;
	}

	return PhaseState::NONE;

	//bool leftPress = mouse_act.Check(MOUSE_LEFT);
	//for (int in = 0; in < BUTTOM_MAX; in++)
	//{
	//	button[in].r = 75.0f;

	//	if (leftPress)
	//	{
	//		if (mouse_input) return PhaseState::NONE;
	//		mouse_input = true;

	//		if (CursorInButtom(in))
	//		{
	//			if(in == Fight)
	//			{
	//				return PhaseState::MOVE_SELECT;
	//			}
	//			else if (in == Change)
	//			{
	//				// Œğ‘ãˆ—
	//				// Œ»İ‚ÍŒğ‘ãˆ—‚ª–¢À‘•‚Ì‚½‚ßANONE‚ğ•Ô‚·
	//				return PhaseState::NONE;  
	//			}
	//		}
	//	}
	//	else
	//	{
	//		mouse_input = false;
	//		button[in].r = 75.0f;
	//	}
	//}

	//return PhaseState::NONE;
}

/// <summary>
/// XVˆ—
/// </summary>
PhaseState CommandPhase::Update()
{
	for (int in = 0; in < BUTTOM_MAX; in++)
	{
		if (CursorInButton(in))
		{
			ChangeButtomColor(in, true);
		}
		else
		{
			ChangeButtomColor(in, false);
		}
	}

	return PhaseState::NONE;
}

/// <summary>
/// •`‰æˆ—
/// </summary>
void CommandPhase::Draw()
{
	for (int draw = 0; draw < BUTTOM_MAX; draw++)
	{
		DrawCircleAA(button[draw].pos.x, button[draw].pos.y, button[draw].r, 100, button[draw].color, 1);
	}

//	DrawFormatString(20, 20, GetColor(255, 255, 255), "%d", mouse_input);
}

/// <summary>
/// ‰¹ºˆ—
/// </summary>
void CommandPhase::Sound()
{
	
}

bool CommandPhase::CursorInButton(int type)
{
	if (CheckCircleHit(button[type].pos, 75.0f, cursor->GetPos(), 10.0f))
	{
		return true;
	}
	return false;
}

void CommandPhase::ChangeButtomColor(int type, bool InFlag)
{
	if (InFlag)
	{
		switch (type)
		{
		case Fight:
			button[Fight].color = GetColor(255, 0, 0);
			break;

		case Change:
			button[Change].color = GetColor(0, 255, 0);
			break;
		}
	}
	else
	{
		switch (type)
		{
		case Fight:
			button[Fight].color = GetColor(175, 0, 0);
			break;

		case Change:
			button[Change].color = GetColor(0, 175, 0);
			break;
		}
	}
}