#pragma once
#include "BattleMonster.h"
#include "MoveData.h"

class EffectApplier
{
public:
	// ランク変動を適用する関数
	void ApplyStatChange(BattleMonster& target, StatType stat, int change);

	// 状態異常を適用する関数
	void ApplyStatusCondition(BattleMonster& target, EffectType effect);

	// ランクをリセットする関数
	void ResetBattleRanks(BattleMonster& mon);

	// ランクの値を倍率に変換するヘルパー関数
	float RankToMultiplier(int rank) const;

	// ランクの値を取得するヘルパー関数
	int GetRank(const BattleMonster& target, StatType stat) const;

	// ランクのポインタを取得するヘルパー関数
	int* GetRankPtr(BattleMonster& target, StatType stat);

	// 速度の実効値を取得するヘルパー関数
	float GetEffectiveSpeed(const BattleMonster& mon) const;

	// 新しいバトルのためにモンスターをリセットする関数
	void ResetForNewBattle(BattleMonster& mon);

	// どく・やけどの継続ダメージ。与えたダメージ量を返す
	int ApplyStatusDamage(BattleMonster& target);  
	
	// まひで行動不能かどうか。true=行動できる
	bool CheckCanAct(BattleMonster& target);       
};