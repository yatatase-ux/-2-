#pragma once
#include "Element.h"

struct BasicState
{
	int ID;
	const char Name[256];
	Element element[2];
	int HP;
	int PATK;
	int PDEF;
	int MATK;
	int MDEF;
	int SPD;
};
