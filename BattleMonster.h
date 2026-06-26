#pragma once
#include "MonsterBaseData.h"

struct BattleMonster
{
	const MonsterBaseData* data;

	int CurrentHP;

	int PATKRank;
	int PDEFRank;
	int MATKRank;
	int MDEFRank;
	int SPDRank;
};