#pragma once
#include "MonsterBaseData.h"
#include "DxLib.h"

class MonsterData
{
protected:

	static const MonsterBaseData monster[];
	static const int MonsterSize;

public:

	static const MonsterBaseData* FindByID(int id);

	static int GetCount();									// ‘”‚ğæ“¾
	static const MonsterBaseData& GetByIndex(int index);	// indexw’è‚Å1‘Ìæ“¾
	static void LoadImages();								// ‰æ‘œ‚ğ“Ç‚İ‚Şê—pŠÖ”

};
