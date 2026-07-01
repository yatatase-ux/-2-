#include "MoveSelectPhase.h"

MoveSelectPhase::MoveSelectPhase(BattleUI* ui, BattleMonster* attacker, BattleMonster* defender)
	: PhaseBase(ui, attacker, defender)
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

		DrawFillBox(x, y, x + 250.0f, y + 75.0f, GetColor(0, 0, 255));
	}
}

void MoveSelectPhase::Sound()
{
	
}
