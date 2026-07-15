#pragma once
#include "PhaseBase.h"
#include "Structure.h"

struct changeButton
{
	FloatXY pos;
	int color;
};

class ChangeMonsPhase : public PhaseBase
{
protected:
	changeButton buttons[3];


public:

	ChangeMonsPhase(Cursor* arg_cursor, Members* arg_pMembers, Members* arg_eMembers, BattleContext* arg_context, InputManager* arg_input);

	PhaseState Input() override;

	PhaseState Update() override;

	void Draw() override;

	void Sound() override;

	bool CursorInButton(int moveID);

	void ChangeColor(int moveID);
};