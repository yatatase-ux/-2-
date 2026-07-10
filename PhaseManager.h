#pragma once
#include <memory>
#include "BattleMonster.h"
#include "InputManager.h"
#include "BattleContext.h"

// フェーズクラスのインクルード
#include "PhaseBase.h"
#include "CommandPhase.h"
#include "MoveSelectPhase.h"
#include "ChangeMonsPhase.h"
#include "ActionPhase.h"
#include "CheckWLPhase.h"

class PhaseManager
{
protected:

	std::unique_ptr<PhaseBase> phase;

	Cursor* cursor;
	BattleContext* context;
	InputManager* input;

	PhaseState currentPhase = PhaseState::COMMAND;

public:

	PhaseManager(Cursor* arg_cursor, BattleContext* arg_context, InputManager* arg_input);

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

