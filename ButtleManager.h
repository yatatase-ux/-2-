#pragma once
#include "BasicState.h"

class Buttle
{
protected:

public:

	Buttle();

	int CalcDamage(
		const BasicState& attacker,
		const BasicState& defender,
		int moveID);

	bool CheckHit();

	void ApplyDamage();
};