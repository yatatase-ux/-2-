#pragma once
#include "MonsterBaseData.h"

enum class StatusCondition
{
	None,
	Poison,
	Paralysis,
	Burn
};

struct BattleMonster
{
	const MonsterBaseData* data = nullptr;							// モンスターの基本データへのポインタ

	int CurrentHP = 0;											// 現在のHP
	int PATKRank = 0;										// 物理攻撃ランク
	int PDEFRank = 0;										// 物理防御ランク
	int MATKRank = 0;										// 特殊攻撃ランク
	int MDEFRank = 0;										// 特殊防御ランク
	int SPDRank = 0;										// すばやさランク

	StatusCondition condition = StatusCondition::None;		// 状態異常の種類を表す列挙型

	int selectedMoveID = -1;								// 選択された技のIDを保持
	int changeMonster = -1;									// 交代先のモンスターを保持

	bool isFainted = false;									// 瀕死かどうかを表すフラッグ

	bool isRevealed = false;								// 一度でも場に出たかを表すフラッグ

};