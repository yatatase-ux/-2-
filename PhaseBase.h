#pragma once
#include <DxLib.h>
#include "Structure.h"
#include "KeyAction.h"
#include "Cursor.h"
#include "BattleMonster.h"
#include "Party.h"
#include "BattleContext.h"
#include "InputManager.h"

enum class PhaseState
{
	NONE,         // 初期状態
	COMMAND,      // 戦う・交代
	MOVE_SELECT,  // 技選択
	CHANGE_MONS,  // 怪獣チェンジ
	ACTION,       // 行動実行
	CHECK_FAINT,  // 戦闘不能判定
	TURN_END,     // ターン終了
	GAME_END      // 試合終了
};

class PhaseBase
{
protected:

	Cursor* cursor;
	Members* members;
	BattleContext* context;
	InputManager* input;

	int Selected_MoveID = -1;

public:

	PhaseBase(Cursor* arg_cursor, Members* arg_members, BattleContext* arg_context, InputManager* arg_input)
		: cursor(arg_cursor), members(arg_members), context(arg_context), input(arg_input) {}

	~PhaseBase() {}

	virtual PhaseState Input() = 0;

	virtual PhaseState Update() = 0;

	virtual void Draw() = 0;

	virtual void Sound() = 0;
};