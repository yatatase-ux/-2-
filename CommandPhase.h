#pragma once
#include "PhaseBase.h"
#include "DamageCalculator.h"
#include "CpuBrain.h"
#include "Button.h"
#include "Commentator.h"

class CommandPhase : public PhaseBase
{
private:
	DamageCalculator damage;
	CpuBrain cpuBrain;
	Commentator commentator;

	Button fightButton;
	Button changeButton;

public:

	PHASE_CLASS(CommandPhase);
};