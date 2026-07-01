#pragma once
#include "PhaseBase.h"
#include "BattleUI.h"

class CommandPhase : public PhaseBase
{
private:
	BattleUI BUI;

public:
	CommandPhase();

	void Input() override;

	void Update() override;

	void Draw() override;

	void Sound() override;
};
