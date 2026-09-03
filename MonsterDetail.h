#pragma once
#include "MonsterBaseData.h"

class MonsterDetail
{
private:

	void DrawStatBar(float x, float y, float maxWidth, int value, int maxValue);

public:

	// x, y はパネルの左上を表す。呼び出し側(各ホスト)が配置場所を決める
	void Draw(const MonsterBaseData& data, float x, float y);
};