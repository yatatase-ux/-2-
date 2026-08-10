#include "ActionPhase.h"

PHASE_CONSTRUCTOR(ActionPhase)
{
	DecideActionOrder();

	time = 120;
	turn = Earlyer;
	turnEnd = false;
	monsDying = false;
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

	if (monsDying) return PhaseState::CHECK_FAINT;

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

/// <summary>
/// 行動順決定処理
/// </summary>
void ActionPhase::DecideActionOrder()
{
	// 交代を選んだ時
	if (context->player->changeMonster >= 0)
	{
		context->player = pMembers->mons[context->player->changeMonster];
		SetActionOrder(TRUE);
	} 
	// 技を選んだ時
	else
	{
		if (context->player->data->SPD > context->enemy->data->SPD)
		{
			SetActionOrder(TRUE);
		}
		else if (context->player->data->SPD < context->enemy->data->SPD)
		{
			SetActionOrder(FALSE);
		}
		else if (context->player->data->SPD == context->enemy->data->SPD)
		{
			if (GetRand(1) == 0)
			{
				SetActionOrder(TRUE);
			}
			else
			{
				SetActionOrder(FALSE);
			}
		}
	}
}

/// <summary>
/// 行動順設定
/// </summary>
/// <param name="playerFirst">プレイヤーが先行かどうか</param>
void ActionPhase::SetActionOrder(bool playerFirst)
{
	if (playerFirst)
	{
		debugText[Earlyer] = "プレイヤーのターン";
		debugText[Later] = "CPUのターン";

		Mons[Earlyer] = context->player;
		Mons[Later] = context->enemy;

		moveID[Earlyer] = context->player->selectedMoveID;
		moveID[Later] = context->enemy->data->MoveID[0];
	}
	else
	{
		debugText[Earlyer] = "CPUのターン";
		debugText[Later] = "プレイヤーのターン";

		Mons[Earlyer] = context->enemy;
		Mons[Later] = context->player;

		moveID[Earlyer] = context->enemy->data->MoveID[0];
		moveID[Later] = context->player->selectedMoveID;
	}
}

/// <summary>
/// ダメージ処理
/// </summary>
void ActionPhase::DamageAction()
{
	time--;

	// 先行
	if (turn == Earlyer)
	{
		if (time > 0)
		{
			int d = damage.CalcDamage(*Mons[Earlyer], *Mons[Later], moveID[Earlyer]);
			DrawString(500, 220, debugText[Earlyer ], GetColor(255, 255, 255));
			DrawString(500, 250, Mons[Earlyer]->data->Name, GetColor(255, 255, 255));
			DrawFormatString(500, 300, GetColor(255, 255, 255), "ダメージ：%d", d);
		}
		else
		{
			ExecuteMove(Mons[Earlyer], Mons[Later], moveID[Earlyer]); // ここを変更
			CheckFaint(Mons[Later]);

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
			int d = damage.CalcDamage( *Mons[Later], *Mons[Earlyer], moveID[Later]);
			DrawString(500, 220, debugText[Later], GetColor(255, 255, 255));
			DrawString(500, 250, Mons[Later]->data->Name, GetColor(255, 255, 255));
			DrawFormatString(500, 300, GetColor(255, 255, 255), "ダメージ：%d", d);
		}
		else
		{
			ExecuteMove(Mons[Later], Mons[Earlyer], moveID[Later]); // ここを変更
			CheckFaint(Mons[Earlyer]);

			turnEnd = true;
		}
	}
}

/// <summary>
/// 瀕死チェック
/// </summary>
/// <param name="after_hp">ダメージ処理後の残りHP</param>
void ActionPhase::CheckFaint(BattleMonster* target)
{
	if (target->CurrentHP <= 0)
	{
		monsDying = true;
		context->faintedMonster = target; // 追加:誰が倒れたかを記録
	}
}

// ActionPhase.cpp
void ActionPhase::ExecuteMove(BattleMonster* attacker, BattleMonster* defender, int moveID)
{
	const MoveData& move = MoveTable[moveID]; // ID(1始まり)と配列index(0始まり)のズレに注意

	if (move.category == MoveCategory::Status)
	{
		// 補助技:ダメージなし
		BattleMonster* target = move.targetSelf ? attacker : defender;
		if (move.effect == EffectType::StatUp || move.effect == EffectType::StatDown)
		{
			effect.ApplyStatChange(*target, move.statIndex, move.statChange);
		}
		else
		{
			effect.ApplyStatusCondition(*target, move.effect);
		}
	}
	else
	{
		// 攻撃技:まずダメージ
		damage.Attack(*attacker, *defender, moveID);

		// 追加効果があれば確率判定(業火拳のやけど、頭突きの素早さダウンなど)
		if (move.effect != EffectType::None && move.effectChance > 0)
		{
			if (GetRand(99) < move.effectChance)
			{
				BattleMonster* target = move.targetSelf ? attacker : defender;
				if (move.effect == EffectType::StatUp || move.effect == EffectType::StatDown)
					effect.ApplyStatChange(*target, move.statIndex, move.statChange);
				else
					effect.ApplyStatusCondition(*target, move.effect);
			}
		}
	}
}