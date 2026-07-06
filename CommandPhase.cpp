#include "CommandPhase.h"

CommandPhase::CommandPhase(Cursor* arg_cursor, BattleContext* arg_context, InputManager* arg_input)
	: PhaseBase(arg_cursor, arg_context, arg_input)
{
	button[Fight] = { 1150.0f, 425.0f, 75.0f, GetColor(175,0,0) };
	button[Change] = { 1150.0f, 600.0f, 75.0f, GetColor(0,175,0) };
}

/// <summary>
/// 入力処理
/// </summary>
PhaseState CommandPhase::Input()
{
	if (InputButton(Fight))
	{
		return PhaseState::MOVE_SELECT;
	}

	if (InputButton(Change))
	{
		// 交代処理をまだ実装していないため、NONEを返す
		return PhaseState::NONE;
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
	//				// 交代処理
	//				// 現在は交代処理が未実装のため、NONEを返す
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
/// 更新処理
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
/// 描画処理
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
/// 音声処理
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
