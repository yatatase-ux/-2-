#pragma once
#include "BattleMonster.h"

class BattleHUD
{
private:
	// 名前+HPバーを指定位置に描画する(alignLeft:名前を左揃えにするか右揃えにするか)
	void DrawHPBar(BattleMonster& mon, float x, float y, float width);
	// 怪獣の画像(仮の円)を指定位置に描画する
	void DrawMonsterImage(float centerX, float centerY, float radius);

	// ランクアイコンを指定位置に描画する
	void DrawRankIcons(BattleMonster& mon, float x, float y);

	// 状態異常マークを指定位置に描画する
	void DrawConditionMark(BattleMonster& mon, float x, float y);

public:

	void UpdateHPAnimation(BattleMonster& mon);		// 表示HPをCurrentHPに近づける
	bool IsHPAnimDone(BattleMonster& mon);			// アニメーションが終わっているか
	void Draw(BattleMonster& player, BattleMonster& enemy);

};