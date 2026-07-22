#pragma once
#include "PhaseBase.h"
#include "Structure.h"

struct changeButton
{
	FloatXY pos;
	int color;
};

class ChangeMonsPhase : public PhaseBase
{
protected:
	changeButton buttons[3];


public:

	PHASE_CLASS(ChangeMonsPhase);


	bool CursorInButton(int moveID);

	void ChangeColor(int moveID);
};