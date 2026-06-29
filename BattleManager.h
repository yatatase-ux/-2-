#pragma once
#include "DamageCalculator.h"

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

public:

	BattleManager();



};

