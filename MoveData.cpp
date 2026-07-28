#include "MoveData.h"
MoveData MoveTable[] =
{
	{ 0, "ŒŠ–„‚ß",   Type::Fire, MoveCategory::Physical, 90, 100, 0 },

	// ===== ‰Î(ID 1~5) =====
	{ 1, "‰Î‰Ša‚è",   Type::Fire, MoveCategory::Physical, 90, 100, 0 },

	{ 2, "‹Æ‰ÎŒ",     Type::Fire, MoveCategory::Physical, 50, 100, 0,
		EffectType::Burn, 25, false },

	{ 3, "‰Î‰Š•úË",   Type::Fire, MoveCategory::Special,  100, 95, 0 },

	{ 4, "‚Ğ‚Ì‚±",     Type::Fire, MoveCategory::Special,  40, 100, 0,
		EffectType::Burn, 10, false },

	{ 5, "“¬u",       Type::Fire, MoveCategory::Status,   0, 100, 0,
		EffectType::StatUp, 100, true, StatType::PhysicalAtk, 1 },

	// ===== …(ID 6~10) =====
	{ 6, "“{““‚ÌˆêŒ‚", Type::Water, MoveCategory::Physical, 90, 100, 0 },

	{ 7, "—â‚½‚¢‰å",   Type::Water, MoveCategory::Physical, 50, 100, 0,
		EffectType::Paralysis, 20, false },

	{ 8, "‚İ‚¸‚Å‚Á‚Û‚¤", Type::Water, MoveCategory::Special, 95, 100, 0 },

	{ 9, "”g“®…",     Type::Water, MoveCategory::Special,  45, 100, 0,
		EffectType::StatDown, 30, false, StatType::MagicAtk, -1 },

	{ 10, "ç‚è‚Ì–¶",  Type::Water, MoveCategory::Status,   0, 100, 0,
		EffectType::StatUp, 100, true, StatType::PhysicalDef, 1 },

	// ===== ‘(ID 11~15) =====
	{ 11, "‚Â‚é‚Ìƒ€ƒ`", Type::Grass, MoveCategory::Physical, 70, 100, 0 },

	{ 12, "‚±‚Ì‚Í",     Type::Grass, MoveCategory::Special,  65, 100, 0 },

	{ 13, "‚Ç‚­‚Ì‰Ô•²", Type::Grass, MoveCategory::Status,   0, 90, 0,

		EffectType::Poison, 100, false },

	{ 14, "‚µ‚Ñ‚ê•²",   Type::Grass, MoveCategory::Status,   0, 75, 0,
		EffectType::Paralysis, 100, false },

	{ 15, "‚©‚ç‚İ‚Â‚­", Type::Grass, MoveCategory::Status,   0, 85, 0,
		EffectType::StatDown, 100, false, StatType::Speed, -1 },

	// ===== –³(ID 16~20) =====
	{ 16, "ŸÓg‚ÌˆêŒ‚", Type::Normal, MoveCategory::Physical, 95, 95, 0 },

	{ 17, "“ª“Ë‚«",     Type::Normal, MoveCategory::Physical, 50, 100, 0,
		EffectType::StatDown, 20, false, StatType::Speed, -1 },

	{ 18, "“¬‹C’e",     Type::Normal, MoveCategory::Special,  95, 95, 0 },

	{ 19, "–Â‚«º",     Type::Normal, MoveCategory::Special,  40, 100, 0,
		EffectType::StatDown, 100, false, StatType::PhysicalAtk, -1 },

	{ 20, "‹C‡‚¢\•ª", Type::Normal, MoveCategory::Status,   0, 100, 1,
		EffectType::StatUp, 100, true, StatType::Speed, 1 },
};
const int MoveTableSize = sizeof(MoveTable) / sizeof(MoveData);