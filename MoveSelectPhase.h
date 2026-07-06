#pragma once
#include "PhaseBase.h"
#include "Function.h"

struct MoveButton
{
	FloatXY pos;
	unsigned int color;
	int moveID;
};

class MoveSelectPhase : public PhaseBase
{
public:
	MoveButton moveButtons[4];

public:
	MoveSelectPhase(Cursor* arg_cursor, BattleMonster* arg_attacker, BattleMonster* arg_defender, InputManager* arg_input);

	PhaseState Input() override;

	PhaseState Update() override;

	void Draw() override;

	void Sound() override;

	bool CursorInMoveButton(int moveID);

	void ChangeColor(int moveID);
};
