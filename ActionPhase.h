#pragma once
#include "PhaseBase.h"

#include "Commentator.h"
#include "BattleHUD.h"

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
	Commentator commentator;

	TurnOrderResult turnOrder;
	StatusTickResult statusResult;

	char baseLineText[ActionMax][128];
	const char* reasoningOnlyLine[ActionMax] = { nullptr, nullptr };
	const char* followUpLine[ActionMax] = { nullptr, nullptr };

	int time;
	int turn;
	bool turnEnd;
	bool monsDying;
	bool showingStatusResult;
	int statusTime;

	BattleHUD battleHUD;

	bool waitingForHPAnim = false;
	bool pendingStatusTickResolution = false;

	void ProcessTurn();

	void AdvanceAfterAction();

	// ó‘ÔˆÙíŒã‚Ì•m€”»’è‹y‚ÑØ‚è‘Ö‚¦
	void ResolveStatusTick();

public:

	PHASE_CLASS(ActionPhase);

};