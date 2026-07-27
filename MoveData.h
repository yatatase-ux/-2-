#pragma once
#include "Element.h"

enum class MoveCategory
{
	Physical,
	Special,
	Status
};

enum class EffectType
{
	None,
	Burn,
	Poison,
	Paralysis,
	StatUp,
	StatDown,
};

enum class StatType
{
	PhysicalAtk,
	PhysicalDef,
	MagicAtk,
	MagicDef,
	Speed
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

	EffectType effect = EffectType::None;
	int effectChance = 0;
	bool targetSelf = false;
	StatType statIndex = StatType::PhysicalAtk; // 能力変化技以外は未使用
	int statChange = 0;
};

extern MoveData MoveTable[];
extern const int MoveTableSize;