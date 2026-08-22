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
	bool playerSwitching = (context->player->changeMonster >= 0);
	bool enemySwitching = (context->enemy->changeMonster >= 0);

	isSwitchAction[Earlyer] = false;
	isSwitchAction[Later] = false;

	// 両者交代の場合
	if (playerSwitching && enemySwitching)
	{
		// 両者交代:殴り合いが発生しないため順序は問わない
		PerformSwitch(context->player, pMembers, Earlyer);
		PerformSwitch(context->enemy, eMembers, Later);
	}
	// プレイヤーが交代、CPUが技の場合
	else if (playerSwitching)
	{
		// 交代は技より優先されるため必ず先攻
		PerformSwitch(context->player, pMembers, Earlyer);
		Mons[Later] = context->enemy;
		moveID[Later] = context->enemy->selectedMoveID;
		debugText[Later] = "CPUのターン";
	}
	// CPUが交代、プレイヤーが技の場合
	else if (enemySwitching)
	{
		PerformSwitch(context->enemy, eMembers, Earlyer);
		Mons[Later] = context->player;
		moveID[Later] = context->player->selectedMoveID;
		debugText[Later] = "プレイヤーのターン";
	}
	// 両者技の場合
	else
	{
		float playerSpeed = effect.GetEffectiveSpeed(*context->player);
		float enemySpeed = effect.GetEffectiveSpeed(*context->enemy);

		if (playerSpeed > enemySpeed) SetActionOrder(TRUE);
		else if (playerSpeed < enemySpeed) SetActionOrder(FALSE);
		else SetActionOrder(GetRand(1) == 0);
	}
}

/// <summary>
/// 交代処理
/// </summary>
/// <param name="contextMon"></param>
/// <param name="members"></param>
/// <param name="slot"></param>
void ActionPhase::PerformSwitch(BattleMonster*& contextMon, Members* members, int slot)
{
	const char* fromName = contextMon->data->Name;						// 交代前の名前を保存
	BattleMonster* newMon = members->mons[contextMon->changeMonster];	// 交代後のモンスターを取得
	contextMon = newMon;												// 交代後のモンスターをBattleContextに反映
	newMon->isRevealed = true;											// 交代後のモンスターを場に出たことにする

	isSwitchAction[slot] = true;										// 交代アクションフラグを立てる
	switchFromName[slot] = fromName;									// 交代前の名前を保存
	switchToName[slot] = newMon->data->Name;							// 交代後の名前を保存
	Mons[slot] = newMon;												// 交代後のモンスターをMonsに反映
	debugText[slot] = (members == pMembers) ? "プレイヤーのターン" : "CPUのターン";
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
		moveID[Later] = context->enemy->selectedMoveID;
	}
	else
	{
		debugText[Earlyer] = "CPUのターン";
		debugText[Later] = "プレイヤーのターン";

		Mons[Earlyer] = context->enemy;
		Mons[Later] = context->player;

		moveID[Earlyer] = context->enemy->selectedMoveID;
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
			DrawString(500, 220, debugText[Earlyer], GetColor(255, 255, 255));

			if (isSwitchAction[Earlyer])
			{
				DrawFormatString(500, 250, GetColor(255, 255, 255),
					"%s→%sへ交代", switchFromName[Earlyer], switchToName[Earlyer]);
			}
			else
			{
				int d = damage.CalcDamage(*Mons[Earlyer], *Mons[Later], moveID[Earlyer]);
				DrawFormatString(500, 250, GetColor(255, 255, 255),
					"%s(%s)", Mons[Earlyer]->data->Name, MoveTable[moveID[Earlyer]].Name);
				DrawFormatString(500, 280, GetColor(255, 255, 255),
					"ダメージ：%d", d);
			}
		}
		else
		{
			if (!isSwitchAction[Earlyer])
			{
				ExecuteMove(Mons[Earlyer], Mons[Later], moveID[Earlyer]);
			}
			// 交代の場合、交代自体はDecideActionOrderで既に完了しているので何もしない

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
			DrawString(500, 220, debugText[Later], GetColor(255, 255, 255));

			if (isSwitchAction[Later])
			{
				DrawFormatString(500, 250, GetColor(255, 255, 255),
					"%s→%sへ交代", switchFromName[Later], switchToName[Later]);
			}
			else
			{
				int d = damage.CalcDamage(*Mons[Later], *Mons[Earlyer], moveID[Later]);
				DrawFormatString(500, 250, GetColor(255, 255, 255),
					"%s(%s)", Mons[Later]->data->Name, MoveTable[moveID[Later]].Name);
				DrawFormatString(500, 280, GetColor(255, 255, 255),
					"ダメージ：%d", d);
			}
		}
		else
		{
			if (!isSwitchAction[Later])
			{
				ExecuteMove(Mons[Later], Mons[Earlyer], moveID[Later]);
			}
			// 交代の場合、交代自体はDecideActionOrderで既に完了しているので何もしない

			CheckFaint(Mons[Earlyer]);
			turnEnd = true;
		}
		return;
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


void ActionPhase::ExecuteMove(BattleMonster* attacker, BattleMonster* defender, int moveID)
{
	const MoveData& move = MoveTable[moveID];

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