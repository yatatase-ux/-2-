#include "MoveExecutor.h"
#include "DxLib.h"

/// <summary>
/// ダメージ予測
/// </summary>
int MoveExecutor::PreviewDamage(BattleMonster* attacker, BattleMonster* defender, int moveID)
{
	// ダメージ計算機を使って、技のダメージを計算する
	return damage.CalcDamage(*attacker, *defender, moveID);
}

/// <summary>
/// 技の実行
/// </summary>
int MoveExecutor::Execute(BattleMonster* attacker, BattleMonster* defender, int moveID)
{
	const MoveData& move = MoveTable[moveID];		// 技のデータを取得
	
	// 補助技
	if (move.category == MoveCategory::Status)				
	{
		// 補助技:ダメージなし
		BattleMonster* target = move.targetSelf ? attacker : defender;					// 対象を決定
		// 能力変化の場合
		if (move.effect == EffectType::StatUp || move.effect == EffectType::StatDown)	
		{
			effect.ApplyStatChange(*target, move.statIndex, move.statChange);			// 能力変化を適用
		}
		// 状態異常の場合
		else
		{
			effect.ApplyStatusCondition(*target, move.effect);							// 状態異常を適用
		}
		return 0;		// ダメージはないので0を返す
	}
	// 攻撃技
	else
	{
		// 攻撃技:まずダメージ
		int before = defender->CurrentHP;											// 攻撃前のHPを記録
		damage.Attack(*attacker, *defender, moveID);								// ダメージ計算機を使って、技のダメージを計算し、HPを減らす
		int dealt = before - defender->CurrentHP;									// 与えたダメージ量を計算

		// 追加効果があれば確率判定(業火拳のやけど、頭突きの素早さダウンなど)
		if (move.effect != EffectType::None && move.effectChance > 0)
		{
			// 乱数で追加効果の発動判定
			if (GetRand(99) < move.effectChance)
			{
				BattleMonster* target = move.targetSelf ? attacker : defender;					// 対象を決定
				if (move.effect == EffectType::StatUp || move.effect == EffectType::StatDown)	// 能力変化の場合
					effect.ApplyStatChange(*target, move.statIndex, move.statChange);			// 能力変化を適用
				else																			// 状態異常の場合
					effect.ApplyStatusCondition(*target, move.effect);							// 状態異常を適用
			}
		}

		return dealt;		// 与えたダメージ量を返す
	}
}