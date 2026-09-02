#include "MoveSelectPhase.h"
#include "Function.h"

PHASE_CONSTRUCTOR(MoveSelectPhase)
{
	for (int i = 0; i < MOVE_SLOT_MAX; i++)
	{
		float x = 1000.0f;
		float y = 350.0f + i * 85.0f;
		int moveID = context->player->data->MoveID[i];

		const char* label = (moveID >= 0) ? MoveTable[moveID].Name : "";
		moveButtons[i] = Button(x, y, 250.0f, 75.0f, label, GetColor(0, 200, 255), GetColor(0, 255, 255));

		if (moveID < 0)
		{
			moveButtons[i].SetDisabled(true); // ‹óƒXƒƒbƒg‚Í‰Ÿ‚¹‚È‚¢‚æ‚¤‚É‚·‚é
		}
	}
}

PhaseState MoveSelectPhase::Input()
{
	if (input->Mouse().Push(MOUSE_RIGHT)) return PhaseState::COMMAND;

	for (int i = 0; i < MOVE_SLOT_MAX; i++)
	{
		if (moveButtons[i].Input(cursor, input))
		{
			context->player->selectedMoveID = context->player->data->MoveID[i];
			return PhaseState::ACTION;
		}
	}
	return PhaseState::NONE;
}

PhaseState MoveSelectPhase::Update()
{
	for (int i = 0; i < MOVE_SLOT_MAX; i++)
	{
		moveButtons[i].Update(cursor);
	}
	return PhaseState::NONE;
}

void MoveSelectPhase::Draw()
{
	for (int i = 0; i < MOVE_SLOT_MAX; i++)
	{
		moveButtons[i].Draw();
	}
}

void MoveSelectPhase::Sound()
{
}