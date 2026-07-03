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
	MoveSelectPhase(Cursor* arg_curosr, BattleMonster* arg_attacker, BattleMonster* arg_defender);

	PhaseState Input() override;

	void Update() override;

	void Draw() override;

	void Sound() override;

	bool CursorInMoveButton(int moveID);

	void ChangeColor(int moveID);
};
