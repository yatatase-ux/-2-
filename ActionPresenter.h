#pragma once
#include "ActionSlot.h"
#include "BattleMonster.h"
#include "MoveExecutor.h"
#include "TurnOrderResolver.h"      // TurnOrderResult
#include "TurnAftermathProcessor.h" // StatusTickResult

/// <summary>
/// 行動フェーズの描画を担当するクラス
/// </summary>
class ActionPresenter
{

public:

	void DrawTurnPreview(int slot, const TurnOrderResult& turnOrder, MoveExecutor& moveExecutor);
	
	void DrawStatusTick(const StatusTickResult& tick);
};