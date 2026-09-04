#pragma once
#include "PhaseBase.h"
#include "BattleHUD.h"
#include "EffectApplier.h"

class CheckFaintPhase : public PhaseBase
{
public:

	BattleHUD battleHUD;

	EffectApplier effect;

	int time;

	bool showingSurvivorStatusTick = false; 
	int survivorStatusTime = 0;            
	const char* survivorStatusName = nullptr; 
	int survivorStatusDamage = 0;     

	PhaseState ResolveOutcome(); // ‚±‚ê‚Ü‚Å‚Ì”»’èˆ—‚ğ‚Ü‚Æ‚ß‚é

public:

	PHASE_CLASS(CheckFaintPhase);

};