#include "ActionPresenter.h"
#include "MoveData.h"
#include "DxLib.h"

/// <summary>
/// ターンの行動プレビューを描画する
/// </summary>
void ActionPresenter::DrawTurnPreview(int slot, const TurnOrderResult& turnOrder, MoveExecutor& moveExecutor)
{
	int other = (slot == Earlyer) ? Later : Earlyer;	// もう一方のスロットを取得

	DrawString(500, 220, turnOrder.debugText[slot], GetColor(255, 255, 255));	// デバッグ用の文字列を描画

	// 交代アクションかどうかを判定
	if (turnOrder.isSwitchAction[slot])
	{
		// 交代アクションの場合、交代前後のモンスター名を描画
		DrawFormatString(500, 250, GetColor(255, 255, 255),
			"%s→%sへ交代", turnOrder.switchFromName[slot], turnOrder.switchToName[slot]);
	}
	// まひで行動不能かどうかを判定
	else if (!turnOrder.canAct[slot])
	{
		// まひで行動不能の場合、行動不能のメッセージを描画
		DrawFormatString(500, 250, GetColor(255, 255, 0),
			"%s はまひで動けない！", turnOrder.mons[slot]->data->Name);
	}
	// 通常の攻撃アクションの場合
	else
	{
		// 通常の攻撃アクションの場合、技名と予測ダメージを描画
		int d = moveExecutor.PreviewDamage(turnOrder.mons[slot], turnOrder.mons[other], turnOrder.moveID[slot]);
		// 技名と予測ダメージを描画
		DrawFormatString(500, 250, GetColor(255, 255, 255),
			"%s(%s)", turnOrder.mons[slot]->data->Name, MoveTable[turnOrder.moveID[slot]].Name);
		// 予測ダメージを描画
		DrawFormatString(500, 280, GetColor(255, 255, 255),
			"ダメージ：%d", d);
	}
}

/// <summary>
/// 状態異常の継続ダメージを描画する
/// </summary>
void ActionPresenter::DrawStatusTick(const StatusTickResult& tick)
{
	// 状態異常の継続ダメージが発生した場合、名前とダメージ量を描画
	if (tick.name[Earlyer] != nullptr)
	{
		// 状態異常の継続ダメージが発生した場合、名前とダメージ量を描画
		DrawFormatString(500, 220, GetColor(255, 255, 0),
			"%s は状態異常のダメージ：%d", tick.name[Earlyer], tick.damage[Earlyer]);
	}
	// 状態異常の継続ダメージが発生した場合、名前とダメージ量を描画
	if (tick.name[Later] != nullptr)
	{
		// 状態異常の継続ダメージが発生した場合、名前とダメージ量を描画
		DrawFormatString(500, 250, GetColor(255, 255, 0),
			"%s は状態異常のダメージ：%d", tick.name[Later], tick.damage[Later]);
	}
}