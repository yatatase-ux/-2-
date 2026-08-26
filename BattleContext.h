#pragma once
#include "BattleMonster.h"
#include "Party.h"          // MEMBER_MAXを使うため明示的に追加(以前はCpuBrain.h経由の間接includeだったため)
#include "CpuDebugTypes.h"  // CpuBrain.h全体ではなく、必要な構造体だけをinclude

struct BattleContext
{
	Party playerParty;   // PrepPartyStageが書き込む
	Members pMember;     // PrepMemberStageが書き込む
	Members eMember;     // CPU側(当面は仮データのまま)

	BattleMonster* player = nullptr;                        // プレイヤーの現在のモンスター
	BattleMonster* enemy = nullptr;                         // CPUの現在のモンスター

	BattleMonster* faintedMonster = nullptr;                // 瀕死になったモンスターのポインタ
	bool isPlayerWin = false;                               // プレイヤーが勝利したかどうかのフラグ
	bool isForcedSwitch = false;							// 強制交代が発生したかどうかのフラグ

	MoveScoreDebug enemyMoveScore[4];						// CPUの技スコアデバッグ情報(4つの技スロット分)
	SwitchScoreDebug enemySwitchScore[MEMBER_MAX - 1];		// CPUの交代スコアデバッグ情報(控えの数分)
};