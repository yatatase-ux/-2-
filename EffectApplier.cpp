#include "EffectApplier.h"
#include "DxLib.h"

void EffectApplier::ApplyStatChange(BattleMonster& target, StatType stat, int change)
{
	int* rank = nullptr;

	switch (stat)
	{
	case StatType::PhysicalAtk: 
		rank = &target.PATKRank; 
		break;

	case StatType::PhysicalDef: 
		rank = &target.PDEFRank; 
		break;

	case StatType::MagicAtk:   
		rank = &target.MATKRank;
		break;

	case StatType::MagicDef:    
		rank = &target.MDEFRank;
		break;

	case StatType::Speed:       
		rank = &target.SPDRank; 
		break;
	}

	if (rank)
	{
		*rank += change;
		if (*rank > 6) *rank = 6; // ランクの上限
		if (*rank < -6) *rank = -6; // ランクの下限
	}
}

void EffectApplier::ApplyStatusCondition(BattleMonster& target, EffectType effect)
{
	// 既に何か状態異常にかかっている場合は上書きしない、という仕様であれば
	if (target.condition != StatusCondition::None) return;

	switch (effect)
	{
	case EffectType::Burn:    
		target.condition = StatusCondition::Burn;    
		break;

	case EffectType::Poison:    
		target.condition = StatusCondition::Poison;  
		break;

	case EffectType::Paralysis: 
		target.condition = StatusCondition::Paralysis; 
		break;

	default: break;
	}
}

void EffectApplier::ResetBattleRanks(BattleMonster& mon)
{
	mon.PATKRank = 0;
	mon.PDEFRank = 0;
	mon.MATKRank = 0;
	mon.MDEFRank = 0;
	mon.SPDRank = 0;
	// condition はリセットしない(状態異常は交代しても持続する)
}

float EffectApplier::RankToMultiplier(int rank) const
{
	if (rank >= 0) 
	{
		return (2.0f + rank) / 2.0f; // 例: +1 → 1.5倍, +2 → 2.0倍
	}
	else 
	{
		return 2.0f / (2.0f - rank); // 例: -1 → 0.66倍, -2 → 0.5倍
	}
}

int EffectApplier::GetRank(const BattleMonster& target, StatType stat) const
{
	switch (stat)
	{
	case StatType::PhysicalAtk: return target.PATKRank;
	case StatType::PhysicalDef: return target.PDEFRank;
	case StatType::MagicAtk:    return target.MATKRank;
	case StatType::MagicDef:    return target.MDEFRank;
	case StatType::Speed:       return target.SPDRank;
	}
	return 0;
}

int* EffectApplier::GetRankPtr(BattleMonster& target, StatType stat)
{
	switch (stat)
	{
	case StatType::PhysicalAtk: return &target.PATKRank;
	case StatType::PhysicalDef: return &target.PDEFRank;
	case StatType::MagicAtk:    return &target.MATKRank;
	case StatType::MagicDef:    return &target.MDEFRank;
	case StatType::Speed:       return &target.SPDRank;
	}
	return nullptr;
}

float EffectApplier::GetEffectiveSpeed(const BattleMonster& mon) const
{
	return mon.data->SPD * RankToMultiplier(mon.SPDRank);
}

void EffectApplier::ResetForNewBattle(BattleMonster& mon)
{
	if (mon.data == nullptr) return; // 空き枠はスキップ

	mon.CurrentHP = mon.data->HP;
	mon.isFainted = false;
	mon.isRevealed = false;
	mon.condition = StatusCondition::None; // 新しい試合なので、ここはリセットして良い
	mon.selectedMoveID = -1;
	mon.changeMonster = -1;

	ResetBattleRanks(mon); // 既存の関数を再利用してランクもリセット
}

int EffectApplier::ApplyStatusDamage(BattleMonster& target)
{
	if (target.condition != StatusCondition::Poison && target.condition != StatusCondition::Burn)
	{
		return 0;
	}

	int dmg = target.data->HP / 8; // 最大HPの1/8。
	target.CurrentHP -= dmg;
	if (target.CurrentHP < 0) target.CurrentHP = 0;
	return dmg;
}

bool EffectApplier::CheckCanAct(BattleMonster& target)
{
	if (target.condition != StatusCondition::Paralysis) return true;
	return GetRand(99) >= 30; // 30%の確率で行動不能
}