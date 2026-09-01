#pragma once
#include "BattleMonster.h"
#include "MoveData.h"
#include "DamageCalculator.h"
#include "EffectApplier.h"

class MoveExecutor
{
private:
	DamageCalculator damage;

	EffectApplier effect;

public:

	int PreviewDamage(BattleMonster* attacker, BattleMonster* defender, int moveID); // 表示用の予測
	
	int Execute(BattleMonster* attacker, BattleMonster* defender, int moveID);       // 実際に技を実行し、与えたダメージ量を返す
};