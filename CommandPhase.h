#pragma once
#include "PhaseBase.h"
#include "DamageCalculator.h"

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

public:

	CommandPhase(Cursor* arg_cursor, Members* arg_pMembers, Members* arg_eMembers, BattleContext* arg_context, InputManager* arg_input);

	PhaseState Input() override;

	PhaseState Update() override;

	void Draw() override;

	void Sound() override;

	bool CursorInButtom(int type);

	void ChangeButtomColor(int type, bool InFlag);

	bool InputButton(int type);
};
