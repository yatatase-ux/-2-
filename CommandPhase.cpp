#include "CommandPhase.h"

CommandPhase::CommandPhase(Cursor* arg_cursor, Members* arg_members, BattleContext* arg_context, InputManager* arg_input)
	: PhaseBase(arg_cursor, arg_members, arg_context, arg_input)
{
	button[Fight] = { 1150.0f, 425.0f, 75.0f, GetColor(175,0,0) };
	button[Change] = { 1150.0f, 600.0f, 75.0f, GetColor(0,175,0) };
}

/// <summary>
/// “ü—Íˆ—
/// </summary>
PhaseState CommandPhase::Input()
{
	bool click = input->Mouse().Push(MOUSE_LEFT);

	if (click)
	{
		if (CursorInButtom(Fight))
			return PhaseState::MOVE_SELECT;

		if (CursorInButtom(Change))
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
		if (CursorInButtom(in))
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

bool CommandPhase::CursorInButtom(int type)
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

bool CommandPhase::InputButton(int type)
{
	if (input->Mouse().Push(MOUSE_LEFT))
	{
		if (CursorInButtom(type))
		{
			return true;
		}
	}

	return false;
}
