#pragma once
#include "PhaseBase.h"
#include "BattleUI.h"
#include "DamageCalculator.h"

class CommandPhase : public PhaseBase
{
private:

	DamageCalculator damage;

public:

	CommandPhase(BattleUI* ui, BattleMonster* attacker, BattleMonster* defender);

	void Input() override;

	void Update() override;

	void Draw() override;

	void Sound() override;

	PhaseState ChangePhase() const override;
};
