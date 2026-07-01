#pragma once
#include "PhaseBase.h"

class MoveSelectPhase : public PhaseBase
{
public:
	MoveSelectPhase(BattleUI* ui, BattleMonster* attacker, BattleMonster* defender);

	PhaseState Input() override;

	void Update() override;

	void Draw() override;

	void Sound() override;
};
