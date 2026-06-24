#pragma once
#include "BasicState.h"

struct BattleMonster
{
	const BasicState* data;

	int CurrentHP;

	int PATKRank;
	int PDEFRank;
	int MATKRank;
	int MDEFRank;
	int SPDRank;
};