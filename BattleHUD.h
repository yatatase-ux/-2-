#pragma once
#include "BattleMonster.h"

class BattleHUD
{
private:
	void DrawMonsterPanel(BattleMonster& mon, float x, float y, float width, bool isPlayerSide);

public:

	void Draw(BattleMonster& player, BattleMonster& enemy);

};