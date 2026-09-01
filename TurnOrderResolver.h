#pragma once
#include "ActionSlot.h"
#include "BattleMonster.h"
#include "Party.h"
#include "BattleContext.h"
#include "EffectApplier.h"

/// <summary>
/// 行動順決定の結果を格納する構造体
/// </summary>
struct TurnOrderResult
{
	BattleMonster* mons[ActionMax];							// 先攻・後攻のモンスターを格納する配列
	int moveID[ActionMax];									// 先攻・後攻の技IDを格納する配列
	bool isSwitchAction[ActionMax] = { false, false };		// 先攻・後攻の交代アクションフラグを格納する配列
	const char* switchFromName[ActionMax] = { "", "" };		// 交代前のモンスター名を格納する配列
	const char* switchToName[ActionMax] = { "", "" };		// 交代後のモンスター名を格納する配列
	const char* debugText[ActionMax] = { "", "" };			// デバッグ用の文字列を格納する配列
	bool canAct[ActionMax] = { true, true };				// まひ判定込み、ここで確定
};

class TurnOrderResolver
{
private:

	EffectApplier effect;

	/// <summary>
	/// 交代処理
	/// </summary>
	void PerformSwitch(BattleMonster*& contextMon, Members* members, bool isPlayerSide,
		TurnOrderResult& result, int slot);

public:

	/// <summary>
	/// 行動順を決定する
	/// </summary>
	TurnOrderResult Resolve(BattleContext* context, Members* pMembers, Members* eMembers);
};