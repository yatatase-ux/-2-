#pragma once
#include "MonsterBaseData.h"
#include "Structure.h"

class MonsterDetail
{
private:

	void DrawStatBar(float x, float y, float maxWidth, int value, int maxValue);

	// 指定した技ボックス(0~3)の位置とサイズを計算する(Draw・当たり判定の両方から呼ぶ
	void ComputeMoveBoxRect(int index, const FloatXY& bSize, float x, float y, 
								FloatXY& outPos, FloatXY& outSize);

public:
	// x, y はパネルの左上を表す。呼び出し側(各ホスト)が配置場所を決める
	void Draw(const MonsterBaseData& data, float x, float y, float width, float height);

	// 技ボックスの矩形を取得する(範囲外のindexならfalseを返す)
	bool GetMoveBoxRect(int index, float x, float y, float width, float height,
							FloatXY& outPos, FloatXY& outSize);
};