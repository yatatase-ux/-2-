#pragma once
#include "PhaseBase.h"

#include "Commentator.h"
#include "BattleHUD.h"
#include "EffectApplier.h"

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

	void ProcessTurn();

	void AdvanceAfterAction();

	EffectApplier effect;				// 状態異常ダメージを直接扱うため

	int statusTickIndex = -1;			// Earlyer=0/Later=1、今どちらを処理中か(-1で未処理)
	bool showingStatusAnnounce = false; // 「どくだ！」のような告知中かどうか
	int statusAnnounceTime = 0;         // アナウンス時間

	void AdvanceStatusTick(); // 次に処理すべき対象を探して告知を始める
	void ResolveStatusTick(); // ダメージ処理が終わったら次の対象へ

public:

	PHASE_CLASS(ActionPhase);

};