#include "MoveDetail.h"
#include "DxLib.h"
#include <cstdio>

void MoveDetail::Draw(const MoveData& move, float x, float y)
{
	DrawFormatString((int)x, (int)y, GetColor(0, 0, 0), "%s", move.Name);

	// 補助技は威力の概念が無いため出し分ける
	if (move.category != MoveCategory::Status)
	{
		DrawFormatString((int)x, (int)(y + 40), GetColor(0, 0, 0), "威力：%d", move.Power);
	}
	DrawFormatString((int)x, (int)(y + 80), GetColor(0, 0, 0), "命中率：%d", move.Accuracy);

	// 追加効果の説明文を組み立てる
	char effectText[128] = "追加効果ナシ";
	if (move.effect != EffectType::None)
	{
		const char* effectName = "";
		switch (move.effect)
		{
		case EffectType::Burn:      effectName = "やけど";   break;
		case EffectType::Poison:    effectName = "どく";     break;
		case EffectType::Paralysis: effectName = "まひ";     break;
		case EffectType::StatUp:    effectName = "能力上昇"; break;
		case EffectType::StatDown:  effectName = "能力低下"; break;
		default: break;
		}
		sprintf_s(effectText, "%d%%の確率で%s", move.effectChance, effectName);
	}
	DrawFormatString((int)x, (int)(y + 120), GetColor(0, 0, 0), "%s", effectText);
}