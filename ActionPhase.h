#pragma once
#include "PhaseBase.h"				// 親クラス
// 依存クラス
#include "ActionSlot.h"
#include "TurnOrderResolver.h"
#include "MoveExecutor.h"
#include "TurnAftermathProcessor.h"
#include "ActionPresenter.h"

class ActionPhase : public PhaseBase
{
private:

	TurnOrderResolver turnOrderResolver;
	MoveExecutor moveExecutor;
	TurnAftermathProcessor aftermath;
	ActionPresenter presenter;

	TurnOrderResult turnOrder;
	StatusTickResult statusResult;

	int time;
	int turn;
	bool turnEnd;
	bool monsDying;
	bool showingStatusResult;
	int statusTime;

	void ProcessTurn();

public:

	PHASE_CLASS(ActionPhase);

};