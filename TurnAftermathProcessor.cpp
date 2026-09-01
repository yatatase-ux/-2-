#include "TurnAftermathProcessor.h"

/// <summary>
/// 瀕死判定
/// </summary>
bool TurnAftermathProcessor::CheckFaint(BattleMonster* target, BattleContext* context)
{
	// もしHPが0以下なら、倒れたことをBattleContextに記録してtrueを返す
	if (target->CurrentHP <= 0)
	{
		context->faintedMonster = target;	// 誰が倒れたかを記録
		return true;						// 瀕死判定
	}

	return false;							// 瀕死でない
}

/// <summary>
/// ターン終了時の継続ダメージ処理
/// </summary>
StatusTickResult TurnAftermathProcessor::ProcessEndOfTurn(BattleMonster* mons[ActionMax], BattleContext* context)
{
	StatusTickResult result;								// 継続ダメージの結果を格納する構造体を初期化

	// どく・やけどの継続ダメージを処理
	for (int slot = 0; slot < ActionMax; slot++)
	{
		int dmg = effect.ApplyStatusDamage(*mons[slot]);	// 継続ダメージを適用し、与えたダメージ量を取得
		// もしダメージが発生した場合、結果に名前とダメージ量を記録
		if (dmg > 0)
		{
			result.name[slot] = mons[slot]->data->Name;		// 継続ダメージを受けた怪獣の名前を記録
			result.damage[slot] = dmg;						// 継続ダメージ量を記録
		}

		// もし瀕死になった場合、結果にフラグを立ててループを抜ける
		if (CheckFaint(mons[slot], context))
		{
			result.causedFaint = true;						// このティック処理自体で新たに瀕死が発生したことを記録
			break; // 以前と同じ理由で、同時多重瀕死を避けるためここで打ち切る
		}
	}

	return result;		// 継続ダメージの結果を返す
}