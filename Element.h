#pragma once

enum class Type
{
	None, 	// ñ≥
	Normal,	// ñ≥ëÆê´
	Fire,	// âŒ
	Water,	// êÖ
	Grass,	// ëê

	Type_MAX
};

constexpr const char* ElementName[] =
{
	"None",
	"Normal",
	"Fire",
	"Water",
	"Grass"
};

constexpr float TypeTable
[(int)Type::Type_MAX]
[(int)Type::Type_MAX] = 
{
	//            NONE NORMAL FIRE WATER GRASS
	/* NONE  */ { 1.0f, 1.0f, 1.0f, 1.0f, 1.0f},
	/* NORMAL*/ { 1.0f, 1.0f, 1.0f, 1.0f, 1.0f},
	/* FIRE  */ { 1.0f, 1.0f, 0.5f, 0.5f, 2.0f},
	/* WATER */ { 1.0f, 1.0f, 2.0f, 0.5f, 0.5f},
	/* GRASS */ { 1.0f, 1.0f, 0.5f, 2.0f, 0.5f}
};