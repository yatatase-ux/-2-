#pragma once
#include "PhaseBase.h"
#include "DamageCalculator.h"

enum
{
	Earlyer,
	Later,

	ActionMax
};


class ActionPhase : public PhaseBase
{
public:

	DamageCalculator damage;

	BattleMonster* Mons[ActionMax];
	int moveID[ActionMax];

	int time;
	int turn;
	bool turnEnd;
	bool monsDying;

	const char* debugText[ActionMax] = {"", ""};

public:

	PHASE_CLASS(ActionPhase);


	void DecideActionOrder();

	void SetActionOrder(bool playerFirst);

	void DamageAction();

	void CheckFaint(BattleMonster* target);
};