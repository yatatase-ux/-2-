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
	PHASE_CLASS(MoveSelectPhase);

	bool CursorInMoveButton(int moveID);

	void ChangeColor(int moveID);
};
