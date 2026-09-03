#include "MonsterDetail.h"
#include "MoveData.h"
#include "DxLib.h"
#include "Function.h"

void MonsterDetail::DrawStatBar(float x, float y, float maxWidth, int value, int maxValue)
{
	// 値を割合に変換し、バーの長さを決める(極端な値でも枠からはみ出さないよう1.0でクランプ)
	float ratio = (float)value / maxValue;
	if (ratio > 1.0f) ratio = 1.0f;
	float width = maxWidth * ratio;
	DrawFillBox((int)x, (int)y, (int)(x + width), (int)(y + 20.0f), GetColor(255, 255, 0));
}

void MonsterDetail::Draw(const MonsterBaseData& data, float x, float y)
{
	// 怪獣名
	DrawFormatString((int)x, (int)y, GetColor(0, 0, 0), "%s", data.Name);

	// 画像(未実装のため、仮の円で代用)
	DrawCircleAA((int)(x + 150), (int)(y + 200), 100, 100, GetColor(150, 150, 200), 1);

	// ステータス6項目をバー表示
	const char* statNames[] = { "HP", "物理攻撃", "物理防御", "魔法攻撃", "魔法防御", "素早さ" };
	int statValues[] = { data.HP, data.PATK, data.PDEF, data.MATK, data.MDEF, data.SPD };
	const int barMaxValue = 150; // バーの基準となる最大値(仮。プレイテストしながら調整)

	for (int i = 0; i < 6; i++)
	{
		float rowY = y + 100 + i * 40.0f;
		DrawFormatString((int)(x + 350), (int)rowY, GetColor(0, 0, 0), "%s", statNames[i]);
		DrawStatBar(x + 480, rowY, 250.0f, statValues[i], barMaxValue);
	}

	// 覚えている技4つ(名前のみ)
	for (int i = 0; i < MOVE_SLOT_MAX; i++)
	{
		int moveID = data.MoveID[i];
		const char* moveName = (moveID >= 0) ? MoveTable[moveID].Name : "";
		int col = i % 2;
		int row = i / 2;
		float boxX = x + 480 + col * 220.0f;
		float boxY = y + 350 + row * 60.0f;
		DrawFillBox((int)boxX, (int)boxY, (int)(boxX + 200), (int)(boxY + 50), GetColor(100, 200, 255));
		DrawCenterText(boxX + 100, boxY + 25, moveName, GetColor(0, 0, 0), 20.0f);
	}
}