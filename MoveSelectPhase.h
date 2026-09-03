#pragma once
#include "PhaseBase.h"
#include "Button.h"
#include "MoveDetail.h"

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

	MoveDetail moveDetail;
	int detailMoveIndex = -1; // -1:非表示。0?3ならそのスロットの技を表示中

public:
	PHASE_CLASS(MoveSelectPhase);

};
