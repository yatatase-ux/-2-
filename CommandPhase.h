#pragma once
#include "PhaseBase.h"
#include "DamageCalculator.h"

enum
{
	Fight,
	Change
};
const int BUTTOM_MAX = 2;

class CommandPhase : public PhaseBase
{
private:

	DamageCalculator damage;

	FloatCircle button[BUTTOM_MAX];

public:

	CommandPhase(Cursor* arg_cursor, BattleMonster* arg_attacker, BattleMonster* arg_defender, InputManager* arg_input);

	PhaseState Input() override;

	PhaseState Update() override;

	void Draw() override;

	void Sound() override;

	bool CursorInButtom(int type);

	void ChangeButtomColor(int type, bool InFlag);

	bool InputButton(int type);
};
