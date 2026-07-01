#pragma once
#include <memory>
#include "DamageCalculator.h"
#include "BattleUI.h"
#include "BattleMonster.h"
#include "PhaseBase.h"
#include "CommandPhase.h"


class BattleManager
{
protected:

//   BattleState state = BattleState::COMMAND;

	std::unique_ptr<PhaseBase> phase;

public:

	BattleManager(BattleUI* ui, BattleMonster* attacker, BattleMonster* defender);

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

