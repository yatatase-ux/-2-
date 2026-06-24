#pragma once
#include "Element.h"
#include "MoveData.h"

enum Move;

struct BasicState
{
	int ID;
	const char* Name;
	Element element[2];
	int HP;
	int PATK;
	int PDEF;
	int MATK;
	int MDEF;
	int SPD;
	int MoveID[4];
};
