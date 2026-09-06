#pragma once
#include "BattleMonster.h"
#include "Party.h"          // MEMBER_MAXを使うため明示的に追加(以前はCpuBrain.h経由の間接includeだったため)
#include "CpuDebugTypes.h"  // CpuBrain.h全体ではなく、必要な構造体だけをinclude
#include "CommentarySituation.h" // CommentarySituationの定義

struct BattleContext
{
	Party* playerParty = nullptr;;									// PrepPartyStageが書き込む
	Party enemyParty;												// CPU側の6体。試合ごとにランダム生成し、プレイヤーと違い持ち越さない

	BattleMonster eBattle[MEMBER_MAX];

	Members pMember;												// PrepMemberStageが書き込む
	Members eMember;												// CPU側(当面は仮データのまま)

	BattleMonster* player = nullptr;								// プレイヤーの現在のモンスター
	BattleMonster* enemy = nullptr;									// CPUの現在のモンスター

	BattleMonster* faintedMonster = nullptr;						// 瀕死になったモンスターのポインタ
	bool isPlayerWin = false;										// プレイヤーが勝利したかどうかのフラグ
	bool isForcedSwitch = false;									// 強制交代が発生したかどうかのフラグ

	MoveScoreDebug enemyMoveScore[4];								// CPUの技スコアデバッグ情報(4つの技スロット分)
	SwitchScoreDebug enemySwitchScore[MEMBER_MAX - 1];				// CPUの交代スコアデバッグ情報(控えの数分)

	CpuDecisionResult predictedPlayerDecision;						// プレイヤー行動予測のデバッグ表示用

	CommentarySituation cpuReasoning = CommentarySituation::None;	// CPUの行動がどのシチュエーションだったか
	char cpuReasoningLine[128] = "";								// CPU行動理由の文字列変数

	BattleMonster* secondFaintedMonster = nullptr;					// 予約中の「もう1体の瀕死」(無ければnullptr)
};