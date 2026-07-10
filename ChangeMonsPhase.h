#pragma once
#include "PhaseBase.h"

class ChangeMonsPhase : public PhaseBase
{
protected:

public:

	ChangeMonsPhase(Cursor* arg_cursor, BattleContext* arg_context, InputManager* arg_input);

	PhaseState Input() override;

	PhaseState Update() override;

	void Draw() override;

	void Sound() override;
};