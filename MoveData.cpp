#include "MoveData.h"
MoveData MoveTable[] =
{
	{ 0, "穴埋め",   Type::Fire, MoveCategory::Physical, 1, 5, 0 },
	// 物理　威力：1　命中：5

	// ===== 火(ID 1~5) =====
	{ 1, "火炎斬り",   Type::Fire, MoveCategory::Physical, 90, 100, 0 },
	// 物理　威力：90　命中：100

	{ 2, "業火拳",     Type::Fire, MoveCategory::Physical, 50, 100, 0,
		EffectType::Burn, 25, false },
	// 物理　威力：50　命中：100　追加効果：25%の確率でやけど

	{ 3, "火炎放射",   Type::Fire, MoveCategory::Special,  100, 95, 0 },
	// 特殊　威力：100　命中：95

	{ 4, "ひのこ",     Type::Fire, MoveCategory::Special,  40, 100, 0,
		EffectType::Burn, 10, false },
	// 特殊　威力：40　命中：100　追加効果：10%の確率でやけど

	{ 5, "闘志",       Type::Fire, MoveCategory::Status,   0, 100, 0,
		EffectType::StatUp, 100, true, StatType::PhysicalAtk, 1 },
	// 補助　命中：100　追加効果：物理攻撃1段階上昇

	// ===== 水(ID 6~10) =====
	{ 6, "怒涛の一撃", Type::Water, MoveCategory::Physical, 90, 100, 0 },
	// 物理　威力：90　命中：100

	{ 7, "冷たい牙",   Type::Water, MoveCategory::Physical, 50, 100, 0,
		EffectType::Paralysis, 20, false },
	// 物理　威力：50　命中：100　追加効果：20%の確率で麻痺

	{ 8, "みずでっぽう", Type::Water, MoveCategory::Special, 95, 100, 0 },
	// 特殊　威力：95　命中：100

	{ 9, "波動水",     Type::Water, MoveCategory::Special,  45, 100, 0,
		EffectType::StatDown, 30, false, StatType::MagicAtk, -1 },
	// 特殊　威力：45　命中：100　追加効果：30%の確率で特殊攻撃1段階下降

	{ 10, "守りの霧",  Type::Water, MoveCategory::Status,   0, 100, 0,
		EffectType::StatUp, 100, true, StatType::PhysicalDef, 1 },
	// 補助　命中：100　追加効果：物理防御1段階上昇

	// ===== 草(ID 11~15) =====
	{ 11, "つるのムチ", Type::Grass, MoveCategory::Physical, 70, 100, 0 },
	// 物理　威力：70　命中：100

	{ 12, "このは",     Type::Grass, MoveCategory::Special,  65, 100, 0 },
	// 特殊　威力：65　命中：100

	{ 13, "どくの花粉", Type::Grass, MoveCategory::Status,   0, 90, 0,
		EffectType::Poison, 100, false },
	// 補助　命中：90　追加効果：100%の確率でどく

	{ 14, "しびれ粉",   Type::Grass, MoveCategory::Status,   0, 75, 0,
		EffectType::Paralysis, 100, false },
	// 補助　命中：75　追加効果：100%の確率で麻痺

	{ 15, "からみつく", Type::Grass, MoveCategory::Status,   0, 85, 0,
		EffectType::StatDown, 100, false, StatType::Speed, -1 },
	// 補助　命中：85　追加効果：100%の確率で素早さ1段階下降

	// ===== 無(ID 16~20) =====
	{ 16, "渾身の一撃", Type::Normal, MoveCategory::Physical, 95, 95, 0 },
	// 物理　威力：95　命中：95

	{ 17, "頭突き",     Type::Normal, MoveCategory::Physical, 50, 100, 0,
		EffectType::StatDown, 20, false, StatType::Speed, -1 },
	// 物理　威力：50　命中：100　追加効果：20%の確率で素早さ1段階下降

	{ 18, "闘気弾",     Type::Normal, MoveCategory::Special,  95, 95, 0 },
	// 特殊　威力：95　命中：95

	{ 19, "鳴き声",     Type::Normal, MoveCategory::Special,  40, 100, 0,
		EffectType::StatDown, 100, false, StatType::PhysicalAtk, -1 },
	// 特殊　威力：40　命中：100　追加効果：100%の確率で物理攻撃1段階下降

	{ 20, "気合い十分", Type::Normal, MoveCategory::Status,   0, 100, 1,
		EffectType::StatUp, 100, true, StatType::Speed, 1 },
	// 補助　命中：100　追加効果：素早さ1段階上昇

	{ 21, "紅葉打ち", Type::Grass, MoveCategory::Physical, 75, 100, 0 }, 
	// 物理　威力：75　命中：100

	{ 22, "紅蓮の葉", Type::Grass, MoveCategory::Special,  75, 100, 0 }, 
	// 特殊　威力：75　命中：100

	{ 23, "熱湯拳",   Type::Fire,  MoveCategory::Physical, 75, 100, 0 }, 
	// 物理　威力：75　命中：100
	
	{ 24, "熱湯",     Type::Fire,  MoveCategory::Special,  70,  95, 0, 
		EffectType::Burn, 20, false }, 
	// 特殊　威力：70　命中：95　追加効果：20%の確率でやけど

	{ 25, "樹液流し", Type::Water, MoveCategory::Physical, 75, 100, 0 }, 
	// 物理　威力：75　命中：100

	{ 26, "森の雫",   Type::Water, MoveCategory::Special,  75, 100, 0 }, 
	// 特殊　威力：75　命中：100

};
const int MoveTableSize = sizeof(MoveTable) / sizeof(MoveData);