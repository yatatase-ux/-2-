#pragma once
#include "ActionSlot.h"
#include "BattleMonster.h"
#include "MoveExecutor.h"
#include "TurnOrderResolver.h"
#include "TurnAftermathProcessor.h"
#include "Function.h"

class ActionPresenter
{
	const FloatXY text = { WINDOW_W / 2.0f, WINDOW_H - 90.0f };
	const float textSize = 20.0f;

public:

	void DrawTurnPreview(int slot, const TurnOrderResult& turnOrder, MoveExecutor& moveExecutor,
		const char* baseLine, const char* reasoningOnlyLine, const char* followUpLine);
	void DrawStatusTick(const StatusTickResult& tick);

};