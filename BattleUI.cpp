#include "BattleUI.h"

BattleUI::BattleUI(Cursor* arg_cursor)
	: cursor(arg_cursor)
{
	button[Fight] = { 1150.0f, 425.0f, 75.0f, GetColor(175,0,0) };
	button[Change] = { 1150.0f, 600.0f, 75.0f, GetColor(0,175,0) };
}

void BattleUI::Input()
{
	bool leftPress = mouse_act.Check(MOUSE_LEFT);
	for (int in = 0; in < BUTTOM_MAX; in++)
	{
		button[in].r = 75.0f;

		if (leftPress)
		{
			mouse_input = true;

			if (CursorInButtom(in))
			{
				button[in].r = 50.0f;
			}
		}
		else
		{
			mouse_input = false;
			button[in].r = 75.0f;
		}
	}
}

void BattleUI::Update()
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
}

void BattleUI::Draw()
{
	for (int draw = 0; draw < BUTTOM_MAX; draw++)
	{
		DrawCircleAA(button[draw].pos.x, button[draw].pos.y, button[draw].r, 100, button[draw].color, 1);
	}

//	DrawFormatString(20, 20, GetColor(255, 255, 255), "%d", mouse_input);

}

void BattleUI::Sound()
{

}

bool BattleUI::CursorInButtom(int type)
{
	if (CheckCircleHit(button[type].pos, 75.0f, cursor->GetPos(), 10.0f))
	{
		return true;
	}
	return false;
}

void BattleUI::ChangeButtomColor(int type, bool InFlag)
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

bool BattleUI::InputButton(int type)
{
	if (mouse_act.Push(MOUSE_LEFT))
	{
		if (CursorInButtom(type))
		{
			return true;
		}
	}

	return false;
}