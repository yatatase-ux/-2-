#include "MoveDetail.h"
#include "DxLib.h"
#include <cstdio>
#include "Function.h"

void MoveDetail::Draw(const MoveData& move, float x, float y)
{
	// 技名(左上、大きめの文字で強調)
	DrawCenterFormatText((int)(x + 200), (int)(y + 40), GetColor(0, 0, 0), 50, "%s", move.Name);

	// 威力・命中率(名前の右側にまとめて配置)
	if (move.category != MoveCategory::Status)
	{
		DrawCenterFormatText((int)(x + 480), (int)(y + 15), GetColor(0, 0, 0), 40, "威力：%d", move.Power);
	}
	DrawCenterFormatText((int)(x + 480), (int)(y + 60), GetColor(0, 0, 0), 40, "命中率：%d", move.Accuracy);

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

	// 追加効果(下段に、大きな枠を敷いて強調)
	DrawFillBox((int)(x + 20), (int)(y + 110), (int)(x + 700), (int)(y + 250), GetColor(220, 220, 220));
	DrawLeftFormatText((int)(x + 40), (int)(y + 135), GetColor(0, 0, 0), 24, "%s", effectText);
}