#pragma once
#include "PhaseBase.h"
#include "DamageCalculator.h"

enum
{
	Fight,
	Change,
	BUTTOM_MAX
};

class CommandPhase : public PhaseBase
{
private:

	DamageCalculator damage;

	FloatCircle button[BUTTOM_MAX];

public:

	PHASE_CLASS(CommandPhase);


	bool CursorInButton(int type);

	void ChangeButtomColor(int type, bool InFlag);
};
