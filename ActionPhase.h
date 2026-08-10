#pragma once
#include "PhaseBase.h"
#include "DamageCalculator.h"
#include "EffectApplier.h"
#include "MoveData.h"

enum
{
	Earlyer,
	Later,

	ActionMax
};


class ActionPhase : public PhaseBase
{
private:

	DamageCalculator damage;

	BattleMonster* Mons[ActionMax];
	int moveID[ActionMax];

	int time;
	int turn;
	bool turnEnd;
	bool monsDying;

	const char* debugText[ActionMax] = {"", ""};

	EffectApplier effect; // ÉÅÉìÉoí«â¡

public:

	PHASE_CLASS(ActionPhase);

	void DecideActionOrder();

	void SetActionOrder(bool playerFirst);

	void DamageAction();

	void CheckFaint(BattleMonster* target);

	void ExecuteMove(BattleMonster* attacker, BattleMonster* defender, int moveID);
};