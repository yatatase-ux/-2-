#pragma once
#include "BasicState.h"
#include "MoveData.h"

class ButtleManager
{
protected:

public:

	ButtleManager();

	int CalcDamage(
		const BasicState& attacker,
		const BasicState& defender,
		int moveID);

	bool CheckHit();

	void ApplyDamage();
};