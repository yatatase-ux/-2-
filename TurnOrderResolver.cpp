#include "TurnOrderResolver.h"
#include "DxLib.h"

/// <summary>
/// 行動順決定処理
/// </summary>
TurnOrderResult TurnOrderResolver::Resolve(BattleContext* context, Members* pMembers, Members* eMembers)
{
	TurnOrderResult result;													// 行動順の結果を格納する構造体を初期化

	bool playerSwitching = (context->player->changeMonster >= 0);			// プレイヤーが交代するかどうかを判定
	bool enemySwitching = (context->enemy->changeMonster >= 0);				// CPUが交代するかどうかを判定

	// 両者交代の場合
	if (playerSwitching && enemySwitching)
	{
		// 両者交代:殴り合いが発生しないため順序は問わない
		PerformSwitch(context->player, pMembers, true, result, Earlyer);	// プレイヤーが先攻
		PerformSwitch(context->enemy, eMembers, false, result, Later);		// CPUが後攻
	}
	// プレイヤーが交代、CPUが技の場合
	else if (playerSwitching)
	{
		// 交代は技より優先されるため必ず先攻
		PerformSwitch(context->player, pMembers, true, result, Earlyer);	// プレイヤーが先攻	
		result.mons[Later] = context->enemy;								// CPUが後攻
		result.moveID[Later] = context->enemy->selectedMoveID;				// CPUの技IDを設定
		result.debugText[Later] = "CPUのターン";							// デバッグ用文字列を設定
	}
	// CPUが交代、プレイヤーが技の場合
	else if (enemySwitching)
	{
		PerformSwitch(context->enemy, eMembers, false, result, Earlyer);	// CPUが先攻
		result.mons[Later] = context->player;								// プレイヤーが後攻
		result.moveID[Later] = context->player->selectedMoveID;				// プレイヤーの技IDを設定
		result.debugText[Later] = "プレイヤーのターン";						// デバッグ用文字列を設定
	}
	// 両者技の場合
	else
	{
		float playerSpeed = effect.GetEffectiveSpeed(*context->player);		// 速度の実効値を取得
		float enemySpeed = effect.GetEffectiveSpeed(*context->enemy);		// 速度の実効値を取得

		bool playerFirst;													// 先攻がプレイヤーかどうかを判定
		if (playerSpeed > enemySpeed) playerFirst = true;					// プレイヤーの方が速い場合は先攻
		else if (playerSpeed < enemySpeed) playerFirst = false;				// CPUの方が速い場合は後攻
		else playerFirst = (GetRand(1) == 0);								// 同速の場合はランダムで先攻を決定		

		// 行動順の結果を設定
		if (playerFirst)	// プレイヤーが先攻の場合
		{
			result.debugText[Earlyer] = "プレイヤーのターン";
			result.debugText[Later] = "CPUのターン";
			result.mons[Earlyer] = context->player;
			result.mons[Later] = context->enemy;
			result.moveID[Earlyer] = context->player->selectedMoveID;
			result.moveID[Later] = context->enemy->selectedMoveID;
		}
		else				// CPUが先攻の場合
		{
			result.debugText[Earlyer] = "CPUのターン";
			result.debugText[Later] = "プレイヤーのターン";
			result.mons[Earlyer] = context->enemy;
			result.mons[Later] = context->player;
			result.moveID[Earlyer] = context->enemy->selectedMoveID;
			result.moveID[Later] = context->player->selectedMoveID;
		}
	}

	// まひ判定をここで一括確定(交代する側は判定不要)
	for (int slot = 0; slot < ActionMax; slot++)
	{
		result.canAct[slot] = result.isSwitchAction[slot] ? true : effect.CheckCanAct(*result.mons[slot]);
	}
	return result;	// 行動順の結果を返す
}

/// <summary>
/// 交代処理
/// </summary>
void TurnOrderResolver::PerformSwitch(BattleMonster*& contextMon, Members* members, bool isPlayerSide,
	TurnOrderResult& result, int slot)
{
	const char* fromName = contextMon->data->Name;								// 交代前の名前を保存
	BattleMonster* newMon = members->mons[contextMon->changeMonster];			// 交代後のモンスターを取得
	contextMon = newMon;														// 交代後のモンスターをBattleContextに反映
	newMon->isRevealed = true;													// 交代後のモンスターを場に出たことにする

	result.isSwitchAction[slot] = true;											// 交代アクションフラグを立てる
	result.switchFromName[slot] = fromName;										// 交代前の名前を保存
	result.switchToName[slot] = newMon->data->Name;								// 交代後の名前を保存
	result.mons[slot] = newMon;													// 交代後のモンスターをMonsに反映
	result.debugText[slot] = isPlayerSide ? "プレイヤーのターン" : "CPUのターン";	// デバッグ用文字列を設定
}