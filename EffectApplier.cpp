#include "EffectApplier.h"

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

float EffectApplier::RankToMultiplier(int rank)
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