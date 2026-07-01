#pragma once
#include <memory>
#include "DamageCalculator.h"
#include "BattleUI.h"
#include "PhaseBase.h"
#include "CommandPhase.h"

enum class BattleState
{
    COMMAND,      // 戦う・交代
    MOVE_SELECT,  // 技選択
    ACTION,       // 行動実行
    CHECK_FAINT,  // 戦闘不能判定
    TURN_END,     // ターン終了
    GAME_END      // 試合終了
};

class BattleManager
{
protected:

    BattleState state = BattleState::COMMAND;

	std::unique_ptr<BattleUI> battleUI = std::make_unique<BattleUI>();

	std::unique_ptr<PhaseBase> phase = std::make_unique<CommandPhase>();

public:

	BattleManager();

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
};

