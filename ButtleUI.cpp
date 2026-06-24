#include "ButtleUI.h"

ButtleUI::ButtleUI(Cursor* arg_cursor)
	: cursor(arg_cursor)
{
	buttom[Fight] = { 1150.0f, 425.0f, 75.0f, GetColor(175,0,0) };
	buttom[Change] = { 1150.0f, 600.0f, 75.0f, GetColor(0,175,0) };
}

void ButtleUI::Input()
{
	for (int in = 0; in < BUTTOM_MAX; in++)
	{
		if (CursorInButtom(in))
		{
			if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)
			{
				mouse_input = true;
				buttom[in].r = 50.0f;
			} 
			else
			{
				mouse_input = false;
				buttom[in].r = 75.0f;
			}
		}
	}
}

void ButtleUI::Update()
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

void ButtleUI::Draw()
{
	for (int draw = 0; draw < BUTTOM_MAX; draw++)
	{
		DrawCircleAA(buttom[draw].pos.x, buttom[draw].pos.y, buttom[draw].r, 100, buttom[draw].color, 1);
	}

	DrawFormatString(20, 20, GetColor(255, 255, 255), "%d", mouse_input);
}

bool ButtleUI::CursorInButtom(int type)
{
	if (CheckCircleHit(buttom[type].pos, buttom[type].r, cursor->GetPos(), 10.0f))
	{
		return true;
	}
	return false;
}

void ButtleUI::ChangeButtomColor(int type, bool InFlag)
{
	if (InFlag)
	{
		switch (type)
		{
		case Fight:
			buttom[Fight].color = GetColor(255, 0, 0);
			break;

		case Change:
			buttom[Change].color = GetColor(0, 255, 0);
			break;
		}
	}
	else
	{
		switch (type)
		{
		case Fight:
			buttom[Fight].color = GetColor(175, 0, 0);
			break;

		case Change:
			buttom[Change].color = GetColor(0, 175, 0);
			break;
		}
	}
}