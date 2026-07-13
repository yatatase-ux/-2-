#include "MoveSelectPhase.h"
#include "Function.h"

MoveSelectPhase::MoveSelectPhase(Cursor* arg_cursor, Members* arg_members, BattleContext* arg_context, InputManager* arg_input)
	: PhaseBase(arg_cursor, arg_members, arg_context, arg_input)
{
	for(int init = 0; init < 4; init++)
	{
		moveButtons[init].pos.x = 1000.0f;
		moveButtons[init].pos.y = 350.0f + init * 85.0f;
		moveButtons[init].color = GetColor(0, 200, 255);
		moveButtons[init].moveID = context->player->data->MoveID[init];
	}
}

PhaseState MoveSelectPhase::Input()
{
	if (input->Mouse().Push(MOUSE_RIGHT)) return PhaseState::COMMAND;

	for (int colorChange = 0; colorChange < 4; colorChange++)
	{
		if (CursorInMoveButton(colorChange))
		{
			if (input->Mouse().Push(MOUSE_LEFT))
			{
				context->player->selectedMoveID = context->player->data->MoveID[colorChange];
				if (context->player->selectedMoveID >= 0)
				{
					// 技選択が有効な場合、次のフェーズに進む
					return PhaseState::ACTION;
				}
			}
		}
	}


	return PhaseState::NONE;
}

PhaseState MoveSelectPhase::Update()
{
	for(int colorChange = 0; colorChange < 4; colorChange++)
	{
		if(CursorInMoveButton(colorChange))
		{
			ChangeColor(colorChange);
		}
		else
		{
			moveButtons[colorChange].color = GetColor(0, 200, 255);
		}
	}

	return PhaseState::NONE;
}

void MoveSelectPhase::Draw()
{
	for (int move = 0; move < 4; move++)
	{
		DrawFillBox(moveButtons[move].pos.x, moveButtons[move].pos.y, 
					moveButtons[move].pos.x + 250.0f, moveButtons[move].pos.y + 75.0f, 
					moveButtons[move].color);

		int moveID = context->player->data->MoveID[move];

		if (moveID >= 0)
		{
			const MoveData& moveData = MoveTable[moveID];

			DrawCenterText(moveButtons[move].pos.x + 125.0f, moveButtons[move].pos.y + 37.5f, moveData.Name, GetColor(0, 0, 0), 24.0f);
		}
	}
}

void MoveSelectPhase::Sound()
{
	
}

bool MoveSelectPhase::CursorInMoveButton(int moveID)
{
	if (CheckPointBoxHit(cursor->GetPos(), moveButtons[moveID].pos, { 250.0f, 75.0f }))
	{
		return true;
	}
	return false;
}

void MoveSelectPhase::ChangeColor(int moveID)
{
	moveButtons[moveID].color = GetColor(0, 255, 255);
}