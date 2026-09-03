#include "MemberDetail.h"
#include "MoveData.h"
#include "Function.h" // DrawStatBar
#include "DxLib.h"

void MemberDetail::Draw(const MonsterBaseData& data, float x, float y)
{
	// 怪獣名(左上)
	SetFontSize(28);
	DrawFormatString((int)(x + 20), (int)(y + 20), GetColor(0, 0, 0), "%s", data.Name);

	// 画像(仮の円、名前の下)
	DrawCircleAA((int)(x + 90), (int)(y + 150), 70, 100, GetColor(150, 150, 200), 1);

	// ステータス6項目(画像の右)
	const char* statNames[] = { "HP", "物理攻撃", "物理防御", "魔法攻撃", "魔法防御", "素早さ" };
	int statValues[] = { data.HP, data.PATK, data.PDEF, data.MATK, data.MDEF, data.SPD };
	const int barMaxValue = 150; // 仮。プレイテストしながら調整

	for (int i = 0; i < 6; i++)
	{
		float rowY = y + 45 + i * 30.0f;
		DrawRightFormatText(x + 330, rowY, GetColor(0, 0, 0), 16.0f, "%s", statNames[i]);
		DrawStatBar(x + 340, rowY - 6.0f, 200.0f, statValues[i], barMaxValue);
	}

	// 技4つ(2×2、右端)
	for (int i = 0; i < MOVE_SLOT_MAX; i++)
	{
		int moveID = data.MoveID[i];
		const char* moveName = (moveID >= 0) ? MoveTable[moveID].Name : "";
		int col = i % 2;
		int row = i / 2;
		float boxX = x + 520 + col * 210.0f;
		float boxY = y + 20 + row * 60.0f;
		DrawFillBox((int)boxX, (int)boxY, (int)(boxX + 190), (int)(boxY + 50), GetColor(100, 200, 255));
		DrawCenterText(boxX + 95, boxY + 25, moveName, GetColor(0, 0, 0), 20.0f);
	}
}