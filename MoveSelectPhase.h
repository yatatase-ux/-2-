#pragma once
#include "PhaseBase.h"
#include "Button.h"

struct MoveButton
{
	FloatXY pos;
	unsigned int color;
	int moveID;
};

class MoveSelectPhase : public PhaseBase
{
public:
	Button moveButtons[MOVE_SLOT_MAX];

public:
	PHASE_CLASS(MoveSelectPhase);

};
