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

// MonsterDetail.cpp
void MonsterDetail::Draw(const MonsterBaseData& data, float x, float y, float width, float height)
{
	FloatXY bSize = { width - x, height - y };

	// フォントサイズはすべてbSize.x(幅)基準の割合で計算する
	// 係数は、PrepPartyStage(bSize.x=1080)で従来のベタ書きサイズ(60/30/35)と一致するよう逆算した値
	float nameSize = bSize.x * 0.0556f;      // 1080 * 0.0556 ≒ 60
	float statLabelSize = bSize.x * 0.0278f; // 1080 * 0.0278 ≒ 30
	float moveTextSize = bSize.x * 0.0324f;  // 1080 * 0.0324 ≒ 35

	// 怪獣名(左上、高さの約9.7%のサイズ)
	FloatXY nPos = { x + (bSize.x * 0.25f), y + (bSize.y * 0.1f) };
	DrawCenterFormatText(nPos.x, nPos.y, GetColor(0, 0, 0), nameSize, "%s", data.Name);

	// 属性(名前の下、中央寄り)
	FloatXY tPos = { x + (bSize.x * 0.75f), y + (bSize.y * 0.1f) };
	if (data.element[1] == Type::None)
	{
		DrawCenterFormatText(tPos.x, tPos.y, GetColor(0, 0, 0), nameSize,
			"属性：%s", ElementNameJP[(int)data.element[0]]);
	}
	else
	{
		DrawCenterFormatText(tPos.x, tPos.y, GetColor(0, 0, 0), nameSize,
			"属性：%s | %s", ElementNameJP[(int)data.element[0]], ElementNameJP[(int)data.element[1]]);
	}

	// 画像(左下寄りの円、仮)
	FloatXY cPos = { x + (bSize.x * 0.25f), y + (bSize.y * 0.6f) };
	float imgRadius = bSize.y * 0.25f;
	DrawCircleAA(cPos.x, cPos.y, (int)imgRadius, 100, GetColor(150, 150, 200), 1);

	// ステータス6項目(中央〜右寄り)
	const char* statNames[] = { "HP", "物理攻撃", "物理防御", "魔法攻撃", "魔法防御", "素早さ" };
	int statValues[] = { data.HP, data.PATK, data.PDEF, data.MATK, data.MDEF, data.SPD };
	const int barMaxValue = 150;
	for (int i = 0; i < 6; i++)
	{
		FloatXY labelPos = { x + (bSize.x * 0.73f), y + (bSize.y * 0.25f) + i * (bSize.y * 0.07f) };
		FloatXY barPos = { x + (bSize.x * 0.75f), labelPos.y - 10.0f };
		float barWidth = bSize.x * 0.25f;
		DrawRightFormatText(labelPos.x, labelPos.y, GetColor(0, 0, 0), statLabelSize, "%s", statNames[i]);
		DrawStatBar(barPos.x, barPos.y, barWidth, statValues[i], barMaxValue);
	}

	// 技4つ(右側、2×2)
	for (int i = 0; i < MOVE_SLOT_MAX; i++)
	{
		int moveID = data.MoveID[i];
		const char* moveName = (moveID >= 0) ? MoveTable[moveID].Name : "";

		FloatXY boxPos, boxSize;
		ComputeMoveBoxRect(i, bSize, x, y, boxPos, boxSize);

		DrawFillBox((int)boxPos.x, (int)boxPos.y, (int)(boxPos.x + boxSize.x), (int)(boxPos.y + boxSize.y), GetColor(100, 200, 255));
		DrawCenterText(boxPos.x + boxSize.x * 0.5f, boxPos.y + boxSize.y * 0.5f, moveName, GetColor(0, 0, 0), moveTextSize);
	}
}

void MonsterDetail::ComputeMoveBoxRect(int index, const FloatXY& bSize, float x, float y, FloatXY& outPos, FloatXY& outSize)
{
	int col = index % 2;
	int row = index / 2;
	outSize = { bSize.x * 0.20f, bSize.y * 0.15f };
	outPos = {
		x + (bSize.x * 0.55f) + col * (outSize.x + bSize.x * 0.02f),
		y + (bSize.y * 0.65f) + row * (outSize.y + bSize.y * 0.03f)
	};
}

bool MonsterDetail::GetMoveBoxRect(int index, float x, float y, float width, float height, FloatXY& outPos, FloatXY& outSize)
{
	if (index < 0 || index >= MOVE_SLOT_MAX) return false;
	FloatXY bSize = { width - x, height - y };
	ComputeMoveBoxRect(index, bSize, x, y, outPos, outSize);
	return true;
}