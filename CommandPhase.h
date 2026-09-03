#pragma once
#include "PhaseBase.h"
#include "DamageCalculator.h"
#include "CpuBrain.h"
#include "Button.h"
#include "Commentator.h"
#include "BattleHUD.h"

class CommandPhase : public PhaseBase
{
private:
	DamageCalculator damage;
	CpuBrain cpuBrain;
	Commentator commentator;

	Button fightButton;
	Button changeButton;

	// 指定されたパーティの生存数が1体以下かどうかを判定するヘルパー
	// (これを倒せば「試合を決める撃破」になる場面かどうかの判定に使う)
	bool CheckMatchPoint(Members* members);

	// ① プレイヤー行動の予測
	CpuDecisionResult PredictPlayerAction(bool isMatchPointForPlayer);

	// ② CPU自身の行動決定(①の予測結果を使う)
	CpuDecisionResult DecideCpuAction(const CpuDecisionResult& predicted, bool isMatchPoint);

	// ③ 実況:CPUの決定理由を判定・記録する(②の結果と①の予測を両方使う)
	void DetermineCommentary(const CpuDecisionResult& decision, const CpuDecisionResult& predicted);

	BattleHUD battleHUD;

public:

	PHASE_CLASS(CommandPhase);


};