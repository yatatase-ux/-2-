#include "BattleHUD.h"
#include "DxLib.h"
#include "Function.h"

void BattleHUD::DrawStatusBar(BattleMonster& mon, float x, float y, float width)
{
	DrawLeftFormatText(x, y, GetColor(0, 0, 0), 30, "%s", mon.data->Name);

	float barY = y + 25.0f;
	DrawFillBox((int)x, (int)barY, (int)(x + width), (int)(barY + 20.0f), GetColor(80, 80, 80)); // 減った分の下地
	DrawStatBar(x, barY, width, mon.CurrentHP, mon.data->HP, GetColor(80, 200, 80)); // HPは緑
}

void BattleHUD::DrawMonsterImage(float centerX, float centerY, float radius)
{
	DrawCircleAA((int)centerX, (int)centerY, (int)radius, 100, GetColor(150, 150, 200), 1);
}

void BattleHUD::Draw(BattleMonster& player, BattleMonster& enemy)
{
	// プレイヤー側:実況欄の上端近くにHPバー、その右上あたりに怪獣
	DrawMonsterImage(450.0f, 480.0f, 100.0f);
	DrawStatusBar(player, 60.0f, 500.0f, 250.0f);

	// CPU側:右上隅にHPバー、その左下あたりに怪獣
	DrawMonsterImage(1000.0f, 150.0f, 100.0f);
	DrawStatusBar(enemy, 950.0f, 40.0f, 250.0f);
}