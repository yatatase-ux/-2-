#include "ChangeMonsPhase.h"

ChangeMonsPhase::ChangeMonsPhase(Cursor* arg_cursor, Members* arg_members, BattleContext* arg_context, InputManager* arg_input)
	: PhaseBase(arg_cursor, arg_members, arg_context, arg_input)
{
	for (int i = 0; i < 3; i++)
	{
		buttons[i].pos.x = 1000.0f;
		buttons[i].pos.y = 350.0f + i * 85.0f;
		buttons[i].color = GetColor(200, 200, 200);
	}
}

PhaseState ChangeMonsPhase::Input()
{
	if (input->Mouse().Push(MOUSE_RIGHT)) return PhaseState::COMMAND;

	for (int i = 0; i < 3; i++)
	{
		if (CursorInButton(i))
		{
			if (input->Mouse().Push(MOUSE_LEFT))
			{
				context->changeMonster = i;

				return PhaseState::ACTION;
			}
		}
	}

	return PhaseState::NONE;
}

PhaseState ChangeMonsPhase::Update()
{
	for (int colorChange = 0; colorChange < 3; colorChange++)
	{
		if (CursorInButton(colorChange))
		{
			ChangeColor(colorChange);
		}
		else
		{
			buttons[colorChange].color = GetColor(100, 100, 100);
		}
	}

	return PhaseState::NONE;
}

void ChangeMonsPhase::Draw()
{
	for (int i = 0; i < 3; i++)
	{
		DrawFillBox(buttons[i].pos.x, buttons[i].pos.y,
			buttons[i].pos.x + 250.0f, buttons[i].pos.y + 75.0f,
			buttons[i].color);


		DrawCenterText(buttons[i].pos.x + 125.0f, buttons[i].pos.y + 37.5f,
						members->mons[i]->data->Name, GetColor(0, 0, 0), 30.0f);
	}
}

void ChangeMonsPhase::Sound()
{

}

bool ChangeMonsPhase::CursorInButton(int moveID)
{
	if (CheckPointBoxHit(cursor->GetPos(), buttons[moveID].pos, { 250.0f, 75.0f }))
	{
		return true;
	}
	return false;
}

void ChangeMonsPhase::ChangeColor(int moveID)
{
	buttons[moveID].color = GetColor(255, 255, 255);
}