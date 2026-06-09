#pragma once
#include "BasicState.h"
#include "DxLib.h"

class MonsterData
{
protected:
	static const BasicState monster[];
	static const int MonsterSize;

public:

	void ShowData();

};
