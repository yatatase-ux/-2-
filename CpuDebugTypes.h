#pragma once
#include "MonsterBaseData.h" // MOVE_SLOT_MAX
#include "Party.h"           // MEMBER_MAX

struct MoveScoreDebug
{
	int moveID = -1;
	int score = 0;
};

struct SwitchScoreDebug
{
	const char* name = "---"; // 追加:未使用スロットでも安全な文字列を指す
	int score = 0;
};

struct CpuDecisionResult 
{
	int selectedMoveID = -1;
	int switchToIndex = -1;
	MoveScoreDebug moveScores[MOVE_SLOT_MAX];
	SwitchScoreDebug switchScores[MEMBER_MAX - 1];
};