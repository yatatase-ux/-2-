#pragma once
#include "BattleMonster.h"

class BattleHUD
{
private:
	// 名前+HPバーを指定位置に描画する(alignLeft:名前を左揃えにするか右揃えにするか)
	void DrawStatusBar(BattleMonster& mon, float x, float y, float width, bool alignLeft);

	// 怪獣の画像(仮の円)を指定位置に描画する
	void DrawMonsterImage(float centerX, float centerY, float radius);

public:

	void Draw(BattleMonster& player, BattleMonster& enemy);

};