#pragma once
#include "Element.h"

enum MoveCategory
{
	PHYSICAL,
	SPECIAL,
	STATUS
};

struct MoveData
{
	int ID;

	const char* Name;

	Type element;

	MoveCategory category;

	int Power;

	int Accuracy;

	int Priority;
};

extern MoveData MoveTable[];
extern const int MoveTableSize;