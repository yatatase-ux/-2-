#pragma once
#include "DxLib.h"
#include "BattleMonster.h"
#include "BattleUI.h"

enum class PhaseState
{
	NONE,         // 初期状態
	COMMAND,      // 戦う・交代
	MOVE_SELECT,  // 技選択
	ACTION,       // 行動実行
	CHECK_FAINT,  // 戦闘不能判定
	TURN_END,     // ターン終了
	GAME_END      // 試合終了
};

class PhaseBase
{
protected:

	BattleUI* ui;
	BattleMonster* attacker;
	BattleMonster* defender;	

public:

	PhaseBase(BattleUI* ui, BattleMonster* attacker, BattleMonster* defender)
		: ui(ui), attacker(attacker), defender(defender) {}

	~PhaseBase() {}

	virtual PhaseState Input() = 0;

	virtual void Update() = 0;

	virtual void Draw() = 0;

	virtual void Sound() = 0;
};