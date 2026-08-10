#pragma once
#include "MonsterBaseData.h"

enum class StatusCondition
{
	None,
	Poison,
	Paralysis,
	Burn
};

struct BattleMonster
{
	const MonsterBaseData* data;

	int CurrentHP;

	int PATKRank = 0;
	int PDEFRank = 0;
	int MATKRank = 0;
	int MDEFRank = 0;
	int SPDRank = 0;

	StatusCondition condition = StatusCondition::None;

	int selectedMoveID = -1;
	int changeMonster = -1;

	bool isFainted = false;
};