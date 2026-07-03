#pragma once
#include <memory>

#include "BattleUI.h"
#include "BattleMonster.h"

// フェーズクラスのインクルード
#include "PhaseBase.h"
#include "CommandPhase.h"
#include "MoveSelectPhase.h"


class BattleManager
{
protected:

	std::unique_ptr<PhaseBase> phase;

	Cursor* cursor;
	BattleMonster* attacker;
	BattleMonster* defender;

	PhaseState currentPhase = PhaseState::COMMAND;

public:

	BattleManager(Cursor* arg_cursor, BattleMonster* arg_attacker, BattleMonster* arg_defender);

	/// <summary>
	/// 入力処理
	/// </summary>
	void Input();

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw();
	
	/// <summary>
	/// サウンド処理
	/// </summary>
	void Sound();

	void ChangePhase(PhaseState nextPhase);

	std::unique_ptr<PhaseBase> CreatePhase(PhaseState state);

	void DrawPhaseForDebug(PhaseState);
};

