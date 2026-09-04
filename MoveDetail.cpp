#include "MoveDetail.h"
#include "DxLib.h"
#include <cstdio>

void MoveDetail::Draw(const MoveData& move, float x1, float y1, float x2, float y2)
{
	int BoxColor = (move.element == Type::Fire ) ? GetColor(255,  40,  15) : // 火属性は赤
				   (move.element == Type::Water) ? GetColor( 30, 144, 255) : // 水属性は青
				   (move.element == Type::Grass) ? GetColor( 34, 139,  34) : // 草属性は緑
												   GetColor(220, 220, 220) ; // 無属性は灰色

	DrawFillBox((int)x1, (int)y1, (int)x2, (int)y2, BoxColor);

	FloatXY bSize = { x2 - x1, y2 - y1 };

	// フォントサイズはbSize.x(幅)基準の割合で計算する
	float nameSize = bSize.x * 0.059f;   // 850 * 0.059 ≒ 50
	float valueSize = bSize.x * 0.047f;  // 850 * 0.047 ≒ 40
	float effectSize = bSize.x * 0.028f; // 850 * 0.028 ≒ 24

	// 技名(左上寄り、大きめの文字で強調)
	FloatXY nPos = { x1 + (bSize.x * 0.29f), y1 + (bSize.y * 0.15f) };
	DrawCenterFormatText(nPos.x, nPos.y, GetColor(0, 0, 0), nameSize, "%s", move.Name);

	// 物理・特殊・補助のカテゴリーを表示
	FloatXY cPos = { x1 + (bSize.x * 0.29f), y1 + (bSize.y * 0.30f) };
	const char* categoryText = (move.category == MoveCategory::Physical) ? "物理" :
								(move.category == MoveCategory::Special) ? "特殊" :
																		   "補助" ;

	int categoryColor = (move.category == MoveCategory::Physical) ? GetColor(100, 0, 0) :
						 (move.category == MoveCategory::Special) ? GetColor(0, 0, 100) :
																	GetColor(0, 100, 0) ;
//	DrawFillBox((int)(cPos.x - 40), (int)(cPos.y - 20), (int)(cPos.x + 40), (int)(cPos.y + 20), GetColor(200, 200, 200));
	DrawCenterFormatText(cPos.x, cPos.y, GetColor(0, 0, 0), valueSize, "%s", categoryText);

	// 威力・命中率(名前の右側にまとめて配置)
	FloatXY powerPos = { x1 + (bSize.x * 0.62f), y1 + (bSize.y * 0.14f) };
	FloatXY accPos = { x1 + (bSize.x * 0.62f), y1 + (bSize.y * 0.28f) };
	if (move.category != MoveCategory::Status)
	{
		DrawCenterFormatText(powerPos.x, powerPos.y, GetColor(0, 0, 0), valueSize, "威力：%d", move.Power);
	}
	else
	{
		DrawCenterFormatText(powerPos.x, powerPos.y, GetColor(0, 0, 0), valueSize, "威力：--");
	}
	DrawCenterFormatText(accPos.x, accPos.y, GetColor(0, 0, 0), valueSize, "命中率：%d", move.Accuracy);

	// 追加効果の説明文を組み立てる
	DrawEffect(move, x1, y1, bSize, effectSize);
}

void MoveDetail::DrawEffect(const MoveData& move, float x, float y, FloatXY bSize, float effectSize)
{
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

		case EffectType::StatUp:    
			switch (move.statIndex)
			{
			case StatType::PhysicalAtk: effectName = "物理攻撃上昇"; break;
			case StatType::PhysicalDef: effectName = "物理防御上昇"; break;
			case StatType::MagicAtk:    effectName = "魔法攻撃上昇"; break;
			case StatType::MagicDef:    effectName = "魔法防御上昇"; break;
			case StatType::Speed:       effectName = "素早さ上昇";   break;
			}
			break;

		case EffectType::StatDown: 
			switch (move.statIndex)
			{
			case StatType::PhysicalAtk: effectName = "物理攻撃低下"; break;
			case StatType::PhysicalDef: effectName = "物理防御低下"; break;
			case StatType::MagicAtk:    effectName = "魔法攻撃低下"; break;
			case StatType::MagicDef:    effectName = "魔法防御低下"; break;
			case StatType::Speed:       effectName = "素早さ低下";   break;
			}
			break;

		default: break;
		}
		sprintf_s(effectText, "%d%%の確率で%s", move.effectChance, effectName);
	}

	// 追加効果(下段に、大きな枠を敷いて強調)
	FloatXY boxStart = { x + (bSize.x * 0.08f), y + (bSize.y * 0.44f) };
	FloatXY boxEnd = { x + (bSize.x * 0.88f), y + (bSize.y * 0.88f) };
	int Gray = 250;
	DrawFillBox((int)boxStart.x, (int)boxStart.y, (int)boxEnd.x, (int)boxEnd.y, GetColor(Gray, Gray, Gray));

	FloatXY effectPos = { x + (bSize.x * 0.11f), y + (bSize.y * 0.52f) };
	DrawLeftFormatText(effectPos.x, effectPos.y, GetColor(0, 0, 0), effectSize, "%s", effectText);
}