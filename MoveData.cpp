#include "MoveData.h"

MoveData MoveTable[] =
{
	{
		0,
		"ñ¬Ç´ê∫",
		Type::Normal,
		SPECIAL,
		40,
		100,
		0
	},
	{
		1,
		"Ç±ÇÃÇÕ",
		Type::Grass,
		SPECIAL,
		40,
		100,
		0
	},
	{
		2,
		"Ç–ÇÃÇ±",
		Type::Fire,
		SPECIAL,
		40,
		100,
		0
	},
	{
		3,
		"Ç›Ç∏Ç≈Ç¡Ç€Ç§",
		Type::Water,
		SPECIAL,
		40,
		100,
		0
	}

};

const int MoveTableSize = sizeof(MoveTable) / sizeof(MoveData);