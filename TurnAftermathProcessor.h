#pragma once
#include "ActionSlot.h"
#include "BattleMonster.h"
#include "BattleContext.h"
#include "EffectApplier.h"

struct StatusTickResult
{
	const char* name[ActionMax] = { nullptr, nullptr }; // 継続ダメージを受けた怪獣の名前(nullptrなら該当なし)
	int damage[ActionMax] = { 0, 0 };					// 継続ダメージ量
	bool causedFaint = false;							// このティック処理自体で新たに瀕死が発生したか
};

/// <summary>
/// ターン終了時の処理をまとめるクラス
/// </summary>
class TurnAftermathProcessor
{
private:
	EffectApplier effect;

public:

	bool CheckFaint(BattleMonster* target, BattleContext* context); // 瀕死なら記録してtrueを返す
	StatusTickResult ProcessEndOfTurn(BattleMonster* mons[ActionMax], BattleContext* context); // ターン終了時の継続ダメージ一式
};