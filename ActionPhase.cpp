#include "ActionPhase.h"

ActionPhase::ActionPhase(Cursor* arg_cursor, BattleContext* arg_context, InputManager* arg_input)
	: PhaseBase(arg_cursor, arg_context, arg_input)
{
	DecideActionOrder();

	time = 120;

	turn = Earlyer;

	turnEnd = false;
}

PhaseState ActionPhase::Input()
{
	// 行動フェーズでは、入力は不要
	return PhaseState::NONE;
}

PhaseState ActionPhase::Update()
{
	// 行動フェーズの更新処理を実装
	DamageAction();

	if (turnEnd) return PhaseState::COMMAND;

	return PhaseState::NONE;
}

void ActionPhase::Draw()
{
	// 行動フェーズの描画処理を実装	
}

void ActionPhase::Sound()
{
	// 行動フェーズの音声処理を実装
}

void ActionPhase::DecideActionOrder()
{
	if (context->player->data->SPD > context->enemy->data->SPD)
	{
		Mons[Earlyer] = context->player;
		Mons[Later] = context->enemy;

		moveID[Earlyer] = context->selectedMoveID;
		moveID[Later] = context->enemy->data->MoveID[0];
	}
	else
	{
		Mons[Later] = context->player;
		Mons[Earlyer] = context->enemy;

		moveID[Later] = context->selectedMoveID;
		moveID[Earlyer] = context->enemy->data->MoveID[0];
	}
}

void ActionPhase::DamageAction()
{
	time--;

	if (turn == Earlyer)
	{
		if (time > 0)
		{
			DrawString(500, 250, Mons[Earlyer]->data->Name, GetColor(255, 255, 255));
		}
		else
		{
			damage.Attack(*Mons[Earlyer], *Mons[Later], moveID[Earlyer]);

			time = 120;
			turn = Later;
		}

		return;
	}

	// 後攻
	if (turn == Later)
	{
		if (time > 0)
		{
			DrawString(500, 250, Mons[Later]->data->Name, GetColor(255, 255, 255));
		}
		else
		{
			damage.Attack(*Mons[Later], *Mons[Earlyer], moveID[Later]);

			turnEnd = true;
		}
	}
}