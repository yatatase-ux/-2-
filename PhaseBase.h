#pragma once
#include <DxLib.h>
#include "Structure.h"
#include "KeyAction.h"
#include "Cursor.h"
#include "BattleMonster.h"

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

	Cursor* cursor;
	BattleMonster* attacker;
	BattleMonster* defender;

	MouseAct mouse_act;
	bool mouse_input = false;

public:

	PhaseBase(Cursor* arg_cursor, BattleMonster* arg_attacker, BattleMonster* arg_defender)
		: cursor(arg_cursor), attacker(arg_attacker), defender(arg_defender) {}

	~PhaseBase() {}

	virtual PhaseState Input() = 0;

	virtual void Update() = 0;

	virtual void Draw() = 0;

	virtual void Sound() = 0;
};