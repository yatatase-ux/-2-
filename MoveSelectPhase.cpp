#include "MoveSelectPhase.h"
#include "Function.h"

MoveSelectPhase::MoveSelectPhase(Cursor* arg_cursor, BattleMonster* arg_attacker, BattleMonster* arg_defender)
	: PhaseBase(arg_cursor, arg_attacker, arg_defender)
{
}

PhaseState MoveSelectPhase::Input()
{
	return PhaseState::NONE;
}

void MoveSelectPhase::Update()
{
	
}

void MoveSelectPhase::Draw()
{
	for (int move = 0; move < 4; move++)
	{
		float x = 1000.0f;
		float y = 350.0f + move * 85.0f;

		DrawFillBox(x, y, x + 250.0f, y + 75.0f, GetColor(0, 200, 255));

		int moveID = attacker->data->MoveID[move];

		if (moveID >= 0)
		{
			const MoveData& moveData = MoveTable[moveID];

			DrawCenterText(x + 125.0f, y + 37.5f, moveData.Name, GetColor(0, 0, 0), 24.0f);
		}
	}
}

void MoveSelectPhase::Sound()
{
	
}
