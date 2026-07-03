#pragma once
#include "PhaseBase.h"

class MoveSelectPhase : public PhaseBase
{
public:
	MoveSelectPhase(Cursor* arg_curosr, BattleMonster* arg_attacker, BattleMonster* arg_defender);

	PhaseState Input() override;

	void Update() override;

	void Draw() override;

	void Sound() override;
};
