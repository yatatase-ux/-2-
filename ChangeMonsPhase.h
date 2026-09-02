#pragma once
#include "PhaseBase.h"
#include "Button.h"

class ChangeMonsPhase : public PhaseBase
{
protected:

	Button buttons[3];

public:

	PHASE_CLASS(ChangeMonsPhase);

};