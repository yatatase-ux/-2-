#pragma once
#include "PhaseBase.h"
#include "DamageCalculator.h"

class ActionPhase : public PhaseBase
{
public:

	DamageCalculator damage;

public:
	ActionPhase(Cursor* arg_cursor, BattleContext* arg_context, InputManager* arg_input);

	PhaseState Input() override;

	PhaseState Update() override;

	void Draw() override;

	void Sound() override;
};