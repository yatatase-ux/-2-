#pragma once
#include "PhaseBase.h"
#include "DamageCalculator.h"
#include "CpuBrain.h"

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

	CpuBrain cpuBrain;

public:

	PHASE_CLASS(CommandPhase);


	bool CursorInButton(int type);

	void ChangeButtomColor(int type, bool InFlag);
};
