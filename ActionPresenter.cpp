#include "ActionPresenter.h"
#include "MoveData.h"
#include "Config.h" // DEBUG_SHOW_DAMAGE

#include "DxLib.h"

/// <summary>
/// ターンの行動プレビューを描画する
/// </summary>
void ActionPresenter::DrawTurnPreview(int slot, const TurnOrderResult& turnOrder, MoveExecutor& moveExecutor,
	const char* baseLine, const char* reactionLine)
{
	DrawString(500, 220, turnOrder.debugText[slot], GetColor(255, 255, 255));

	if (turnOrder.isSwitchAction[slot])
	{
		DrawCenterFormatText(text.x, text.y, GetColor(255, 255, 255), textSize,
			"%s→%sへ交代！", turnOrder.switchFromName[slot], turnOrder.switchToName[slot]);
	}
	else if (!turnOrder.canAct[slot])
	{
		DrawCenterFormatText(text.x, text.y, GetColor(255, 255, 0), textSize,
			"%s はまひで動けない！", turnOrder.mons[slot]->data->Name);
	}
	else if (!turnOrder.willHit[slot])
	{
		DrawCenterFormatText(text.x, text.y, GetColor(255, 255, 0), textSize,
			"%s の攻撃は外れた！", turnOrder.mons[slot]->data->Name);
	}
	else
	{
		DrawCenterFormatText(text.x, text.y, GetColor(255, 255, 255), textSize, "%s", baseLine);
		if (reactionLine != nullptr)
		{
			DrawCenterFormatText(text.x, text.y + textSize, GetColor(255, 255, 0), textSize, "%s", reactionLine);
		}

		// デバッグ用ダメージ数値(画面左上、実況欄とは独立)
		if (DEBUG_SHOW_DAMAGE)
		{
			int otherSlot = (slot == Earlyer) ? Later : Earlyer;
			int d = moveExecutor.PreviewDamage(turnOrder.mons[slot], turnOrder.mons[otherSlot], turnOrder.moveID[slot]);
			DrawFormatString(20, 40, GetColor(255, 255, 0), "ダメージ：%d", d);
		}
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
		DrawCenterFormatText(text.x, text.y, GetColor(255, 255, 0), textSize,
			"%s は状態異常のダメージ：%d", tick.name[Earlyer], tick.damage[Earlyer]);
	}
	// 状態異常の継続ダメージが発生した場合、名前とダメージ量を描画
	if (tick.name[Later] != nullptr)
	{
		// 状態異常の継続ダメージが発生した場合、名前とダメージ量を描画
		DrawCenterFormatText(text.x, text.y + 60, GetColor(255, 255, 0), textSize,
			"%s は状態異常のダメージ：%d", tick.name[Later], tick.damage[Later]);
	}
}