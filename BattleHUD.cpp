#include "BattleHUD.h"
#include "DxLib.h"
#include "Function.h"

void BattleHUD::DrawHPBar(BattleMonster& mon, float x, float y, float width)
{
	DrawLeftFormatText(x, y, GetColor(0, 0, 0), 30, "%s", mon.data->Name);

	float barY = y + 25.0f;
	DrawFillBox((int)x, (int)barY, (int)(x + width), (int)(barY + 20.0f), GetColor(80, 80, 80));	// 減った分の下地
	int color =	(mon.displayedHP <= mon.data->HP / 4) ? GetColor(200, 80, 80)			// HPが1/4以下なら赤
			 : (mon.displayedHP <= mon.data->HP / 2) ? GetColor(200, 200, 80)			// HPが1/2以下なら黄色
													: GetColor(80, 200, 80);		// HPが1/2以上なら緑
	DrawStatBar(x, barY, width, (int)mon.displayedHP, mon.data->HP, color);				// HPバーの描画

}

void BattleHUD::DrawMonsterImage(float centerX, float centerY, float radius)
{
	DrawCircleAA((int)centerX, (int)centerY, (int)radius, 100, GetColor(150, 150, 200), 1);
}


void BattleHUD::DrawRankIcons(BattleMonster& mon, float x, float y)
{
	// 各能力ランクを、表示用の文字とセットでまとめて扱う
	struct RankEntry { const char* letter; int rank; };
	RankEntry ranks[] = {
		{ "A", mon.PATKRank }, // 物理攻撃
		{ "B", mon.PDEFRank }, // 物理防御
		{ "C", mon.MATKRank }, // 魔法攻撃
		{ "D", mon.MDEFRank }, // 魔法防御
		{ "S", mon.SPDRank }   // 素早さ
	};

	float iconRadius = 20.0f;
	float spacing = 50.0f; // アイコン同士の間隔
	float drawX = x;

	for (int i = 0; i < 5; i++)
	{
		if (ranks[i].rank == 0) continue; // 変化が無い項目はそもそも表示しない

		bool isUp = (ranks[i].rank > 0);
		unsigned int color = isUp ? GetColor(220, 50, 50) : GetColor(50, 120, 220); // 上昇:赤、下降:青
		int magnitude = isUp ? ranks[i].rank : -ranks[i].rank; // 絶対値(符号は色で表現済みなので数字は正の値のみ)

		DrawCircleAA((int)drawX, (int)y, (int)iconRadius, 100, color, TRUE);
		DrawCenterFormatText(drawX, y, GetColor(255, 255, 255), 22.0f, "%s", ranks[i].letter);

		// 段階の数字を、円の右下に少し被せて表示
		DrawFormatString((int)(drawX + iconRadius * 0.4f), (int)(y + iconRadius * 0.2f), GetColor(255, 255, 0), "%d", magnitude);

		drawX += spacing; // 表示した分だけ、次のアイコンの位置をずらす
	}
}

// 状態異常マークを描画する
void BattleHUD::DrawConditionMark(BattleMonster& mon, float x, float y)
{
	if (mon.condition == StatusCondition::None) return; // 状態異常が無ければ何も描かない

	const char* label = "";
	unsigned int color = 0;

	switch (mon.condition)
	{
	case StatusCondition::Poison:
		label = "毒";
		color = GetColor(150, 50, 200); // 紫
		break;
	case StatusCondition::Paralysis:
		label = "痺";
		color = GetColor(220, 200, 30); // 黄
		break;
	case StatusCondition::Burn:
		label = "火";
		color = GetColor(230, 120, 30); // 橙
		break;
	default:
		return;
	}

	float radius = 18.0f;
	DrawCircleAA((int)x, (int)y, (int)radius, 100, color, TRUE);
	DrawCenterFormatText(x, y, GetColor(255, 255, 255), 20.0f, "%s", label);
}

void BattleHUD::UpdateHPAnimation(BattleMonster& mon)
{
	const float hpAnimSpeed = 2.0f;
	float target = (float)mon.CurrentHP;

	if (mon.displayedHP > target)
	{
		mon.displayedHP -= hpAnimSpeed;
		if (mon.displayedHP < target) mon.displayedHP = target;
	}
	else
	{
		mon.displayedHP = target;
	}
}

bool BattleHUD::IsHPAnimDone(BattleMonster& mon)
{
	return mon.displayedHP <= (float)mon.CurrentHP;
}

void BattleHUD::Draw(BattleMonster& player, BattleMonster& enemy)
{
	// プレイヤー側:実況欄の上端近くにHPバー、その右上あたりに怪獣
	if(!player.isFainted)
	{
		DrawMonsterImage(450.0f, 480.0f, 100.0f);
		DrawHPBar(player, 60.0f, 500.0f, 250.0f);
		DrawConditionMark(player, 220.0f, 500.0f);
		DrawRankIcons(player, 75.0f, 570.0f); // HPバーのすぐ下
	}

	if (!enemy.isFainted)
	{
		// CPU側:右上隅にHPバー、その左下あたりに怪獣
		DrawMonsterImage(1000.0f, 150.0f, 100.0f);
		DrawHPBar(enemy, 950.0f, 40.0f, 250.0f);
		DrawConditionMark(enemy, 1110.0f, 40.0f);
		DrawRankIcons(enemy, 965.0f, 110.0f); // HPバーのすぐ下
	}
}