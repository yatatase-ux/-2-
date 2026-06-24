#pragma once
#include "MonsterBaseData.h"
#include "MoveData.h"

class ButtleManager
{
protected:

public:

	ButtleManager();

	int CalcDamage(
		const MonsterBaseData& attacker,
		const MonsterBaseData& defender,
		int moveID);

	bool CheckHit();

	void ApplyDamage();
};