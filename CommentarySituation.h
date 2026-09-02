#pragma once

enum class CommentarySituation
{
	None,					// 特筆すべき点なし(反応コメント無し)
	MatchPointKO,			// 試合終了の一撃
	PriorityKill,			// 優先度の高いキル
	NormalKO,				// 通常のキル
	PriorityEscape,			// 優先度の高い逃走
	SuperEffective,			// 効果は抜群
	NotVeryEffective,		// 効果はいまひとつ

	RiskyBoost,				// リスク承知の積み技(最優先)
	BoostSpeed,				// 素早さ上昇で逆転
	BoostOffense,			// 火力を溜める
	BoostDefense,			// 守りを固める
	InflictStatusDamage,	// どく・やけど技
	InflictParalysis,		// まひ技
	Debuff					// 能力低下技
};