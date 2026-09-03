#include "BattleHUD.h"
#include "DxLib.h"
#include "Function.h"

void BattleHUD::DrawMonsterPanel(BattleMonster& mon, float x, float y, float width, bool isPlayerSide)
{
	// 名前(プレイヤー側は左揃え、CPU側は右揃え。互いに向き合うイメージ)
	if (isPlayerSide)
		DrawLeftFormatText(x, y, GetColor(0, 0, 0), 30, "%s", mon.data->Name);
	else
		DrawRightFormatText(x + width, y, GetColor(0, 0, 0), 30, "%s", mon.data->Name);

	// HPバー(名前の下)
	float barY = y + 25.0f;
	DrawFillBox((int)x, (int)barY, (int)(x + width), (int)(barY + 20.0f), GetColor(80, 80, 80)); // 減った分の下地
	DrawStatBar(x, barY, width, mon.CurrentHP, mon.data->HP, GetColor(80, 200, 80)); // HPは緑

	// 画像(仮の円、バーの下)
	float imgCenterY = y + 120.0f;
	DrawCircleAA((int)(x + width * 0.5f), (int)imgCenterY, 60, 100, GetColor(150, 150, 200), 1);
}

void BattleHUD::Draw(BattleMonster& player, BattleMonster& enemy)
{
	// CPU側(右上)
	DrawMonsterPanel(enemy, 800.0f, 30.0f, 400.0f, false);
	// プレイヤー側(左寄り、画面上半分の下の方)
	DrawMonsterPanel(player, 80.0f, 350.0f, 400.0f, true);
}