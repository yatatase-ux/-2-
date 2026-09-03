#pragma once
#include "PhaseBase.h"
#include "BattleHUD.h"

class CheckFaintPhase : public PhaseBase
{
public:

	BattleHUD battleHUD;

public:

	PHASE_CLASS(CheckFaintPhase);

};