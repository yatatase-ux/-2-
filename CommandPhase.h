#pragma once
#include "PhaseBase.h"
#include "DamageCalculator.h"
#include "CpuBrain.h"
#include "EffectApplier.h"
#include "Button.h"

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

	CpuBrain cpuBrain;

	Button fightButton;
	Button changeButton;

public:

	PHASE_CLASS(CommandPhase);

};
