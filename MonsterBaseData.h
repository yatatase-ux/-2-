#pragma once
#include "Element.h"
#include "MoveData.h"

enum Move;

const int MOVE_SLOT_MAX = 4; // 1‘Ì‚ªŠo‚¦‚ç‚ê‚é‹Z‚ÌÅ‘å”

struct MonsterBaseData
{
	int ID;
	const char* Name;
	Type element[2];
	int HP;
	int PATK;
	int PDEF;
	int MATK;
	int MDEF;
	int SPD;
	int MoveID[MOVE_SLOT_MAX];
};
