#pragma once
#include "PhaseBase.h"
#include "BattleHUD.h"
#include "EffectApplier.h"

class CheckFaintPhase : public PhaseBase
{
public:

	BattleHUD battleHUD;

	EffectApplier effect;

public:

	PHASE_CLASS(CheckFaintPhase);

};