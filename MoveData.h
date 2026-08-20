#pragma once
#include "Element.h"

/// <summary>
/// 技の分類
/// </summary>
enum class MoveCategory
{
	Physical,									// 物理
	Special,									// 魔法
	Status										// 補助
};

/// <summary>
/// 追加効果の種類
/// </summary>
enum class EffectType
{
	None,										// 追加効果なし
	Burn,										// やけど
	Poison,										// どく
	Paralysis,									// まひ
	StatUp,										// 能力上昇
	StatDown,									// 能力下降
};

/// <summary>
/// 変化させる能力の対象
/// </summary>
enum class StatType
{
	PhysicalAtk,								// 物理攻撃
	PhysicalDef,								// 物理防御
	MagicAtk,									// 魔法攻撃
	MagicDef,									// 魔法防御
	Speed										// 素早さ
};

struct MoveData
{
	int ID;										// 技ID
	const char* Name;							// 技名
	Type element;								// 属性
	MoveCategory category;						// 物理・魔法・補助の分類
	int Power;									// 威力
	int Accuracy;								// 命中率（％）
	int Priority;								// 優先度

	EffectType effect = EffectType::None;		// 追加効果の種類
	int effectChance = 0;						// 追加効果の発動確率（％）
	bool targetSelf = false;					// 対象が自分か相手か
	StatType statIndex = StatType::PhysicalAtk; // どの能力を変化させるか
	int statChange = 0;							// 対象の能力を何段階変化させるか
};

extern MoveData MoveTable[];
extern const int MoveTableSize;