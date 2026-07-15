#pragma once
#include "PhaseBase.h"

class EndGamePhase : public PhaseBase
{
protected:

public:

	EndGamePhase(Cursor* arg_cursor, Members* arg_pMembers, Members* arg_eMembers, BattleContext* arg_context, InputManager* arg_input);

	PhaseState Input() override;

	PhaseState Update() override;

	void Draw() override;

	void Sound() override;
};
