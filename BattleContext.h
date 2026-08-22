#pragma once
#include "BattleMonster.h"
#include "CpuBrain.h"

struct BattleContext
{
	BattleMonster* player = nullptr;                        // プレイヤーの現在のモンスター
	BattleMonster* enemy = nullptr;                         // CPUの現在のモンスター

	BattleMonster* faintedMonster = nullptr;                // 瀕死になったモンスターのポインタ
	bool isPlayerWin = false;                               // プレイヤーが勝利したかどうかのフラグ
	bool isForcedSwitch = false;							// 強制交代が発生したかどうかのフラグ

	MoveScoreDebug enemyMoveScore[4];						// CPUの技スコアデバッグ情報(4つの技スロット分)
	SwitchScoreDebug enemySwitchScore[MEMBER_MAX - 1];		// CPUの交代スコアデバッグ情報(控えの数分)
};