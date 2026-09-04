#include "ActionPresenter.h"
#include "MoveData.h"
#include "Config.h"
#include "DxLib.h"

void ActionPresenter::DrawTurnPreview(int slot, const TurnOrderResult& turnOrder, MoveExecutor& moveExecutor,
	const char* baseLine, const char* reasoningOnlyLine, const char* followUpLine)
{
	// 背景を暗くして文字を見やすくする
	DrawFillBox(0, 600, WINDOW_W, WINDOW_H, GetColor(75, 75, 75));
	// デバッグ用の文字列を画面上に表示する
//	DrawString(500, 220, turnOrder.debugText[slot], GetColor(255, 255, 255));

	if (turnOrder.isSwitchAction[slot])
	{
		if (reasoningOnlyLine != nullptr)
		{
			DrawCenterFormatText(text.x, text.y, GetColor(255, 255, 255), textSize, "%s", reasoningOnlyLine);
		}
		else
		{
			DrawCenterFormatText(text.x, text.y, GetColor(255, 255, 255), textSize,
				"%s→%sへ交代！", turnOrder.switchFromName[slot], turnOrder.switchToName[slot]);
		}

		if (followUpLine != nullptr)
		{
			DrawCenterFormatText(text.x, text.y + textSize, GetColor(255, 200, 0), textSize, "%s", followUpLine);
		}
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
		if (reasoningOnlyLine != nullptr)
		{
			DrawCenterFormatText(text.x, text.y, GetColor(255, 255, 255), textSize, "%s", reasoningOnlyLine);
		}
		else
		{
			DrawCenterFormatText(text.x, text.y, GetColor(255, 255, 255), textSize, "%s", baseLine);
		}

		if (followUpLine != nullptr)
		{
			DrawCenterFormatText(text.x, text.y + textSize, GetColor(255, 200, 0), textSize, "%s", followUpLine);
		}

		if (DEBUG_SHOW_DAMAGE)
		{
			int otherSlot = (slot == Earlyer) ? Later : Earlyer;
			int d = moveExecutor.PreviewDamage(turnOrder.mons[slot], turnOrder.mons[otherSlot], turnOrder.moveID[slot]);
			DrawFormatString(20, 40, GetColor(255, 255, 0), "ダメージ：%d", d);
		}
	}
}

void ActionPresenter::DrawStatusTick(const StatusTickResult& tick)
{
	if (tick.name[Earlyer] != nullptr)
	{
		DrawCenterFormatText(text.x, text.y, GetColor(255, 255, 0), textSize,
			"%s は状態異常のダメージ：%d", tick.name[Earlyer], tick.damage[Earlyer]);
	}
	if (tick.name[Later] != nullptr)
	{
		DrawCenterFormatText(text.x, text.y + textSize, GetColor(255, 255, 0), textSize,
			"%s は状態異常のダメージ：%d", tick.name[Later], tick.damage[Later]);
	}
}