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
	ActionPhase(Cursor* arg_cursor, BattleContext* arg_context, InputManager* arg_input);

	PhaseState Input() override;

	PhaseState Update() override;

	void Draw() override;

	void Sound() override;

	void DecideActionOrder();

	void SetActionOrder(bool playerFirst);

	void DamageAction();

	void CheckFaint(int after_hp);
};