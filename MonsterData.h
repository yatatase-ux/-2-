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

	static int GetCount();                             // ’Ç‰Á:‘”‚ğæ“¾
	static const MonsterBaseData& GetByIndex(int index); // ’Ç‰Á:indexw’è‚Å1‘Ìæ“¾

};
