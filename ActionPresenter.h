#pragma once
#include "ActionSlot.h"
#include "BattleMonster.h"
#include "MoveExecutor.h"
#include "TurnOrderResolver.h"      // TurnOrderResult
#include "TurnAftermathProcessor.h" // StatusTickResult
#include "Function.h"

/// <summary>
/// 行動フェーズの描画を担当するクラス
/// </summary>
class ActionPresenter
{

	const FloatXY text = {WINDOW_W / 2.0f, WINDOW_H - 90.0f};
	const float textSize = 30.0f;

public:

	void DrawTurnPreview(int slot, const TurnOrderResult& turnOrder, MoveExecutor& moveExecutor,
							const char* baseLine, const char* reactionLine);
	
	void DrawStatusTick(const StatusTickResult& tick);

};