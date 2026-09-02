#include "Commentator.h"
#include "MoveData.h"
#include "DxLib.h"

/// <summary>
/// 状況を分類する
/// </summary>
CommentarySituation Commentator::Classify(BattleMonster& self, BattleMonster& opponent, int moveID, bool isMatchPoint)
{
	const MoveData& move = MoveTable[moveID];

	if (move.category == MoveCategory::Status)
	{
		return statusClassifier.Classify(self, opponent, moveID, damageCalc);
	}
	return attackClassifier.Classify(self, opponent, moveID, damageCalc, isMatchPoint);
}

/// <summary>
/// コメントを生成する
/// </summary>
const char* Commentator::Comment(BattleMonster& self, BattleMonster& opponent, int moveID, bool isMatchPoint)
{
	CommentarySituation situation = Classify(self, opponent, moveID, isMatchPoint);
	if (situation == CommentarySituation::None) return nullptr;
	return PickLine(situation);
}

/// <summary>
/// 状況に応じたセリフを選ぶ
/// </summary>
const char* Commentator::PickLine(CommentarySituation situation)
{
	switch (situation)
	{
	// 試合終了の一撃
	case CommentarySituation::MatchPointKO:
	{
		static const char* lines[] = {
			"これで勝負あり！",
			"決めた…！試合終了だ！",
			"最後の一体、逃さなかった！",
			"長い戦いに、ついに終止符が打たれる…！"
		};
		return lines[GetRand(3)];
	}
	// 優先度の高いキル
	case CommentarySituation::PriorityKill:
	{
		static const char* lines[] = {
			"反応を許さない、先制の一撃！",
			"動く前に決着をつけた！",
			"一瞬の隙も与えない！"
		};
		return lines[GetRand(2)];
	}
	// 通常のキル
	case CommentarySituation::NormalKO:
	{
		static const char* lines[] = {
			"一体、沈めた！",
			"着実に仕留めてきた！",
			"これで数的有利だ！"
		};
		return lines[GetRand(2)];
	}
	// 優先度の高い逃走
	case CommentarySituation::PriorityEscape:
	{
		static const char* lines[] = {
			"これを外せば終わっていた、際どい先手！",
			"生き残るための渾身の一手！",
			"土壇場で先手を選んだ！",
			"一撃で決めるには威力が足りない…それでも、意地を見せる先制の一手！",
			"もはや形勢は決している。それでも、最後まで抗う姿勢を見せた！"
		};
		return lines[GetRand(4)];
	}
	// 効果は抜群
	case CommentarySituation::SuperEffective:
	{
		static const char* lines[] = {
			"見事に弱点を突いた！",
			"効果は抜群…！",
			"これが刺さらないわけがない！"
		};
		return lines[GetRand(2)];
	}
	// 効果はいまひとつ
	case CommentarySituation::NotVeryEffective:
	{
		static const char* lines[] = {
			"上手く受けました！",
			"相性はいまひとつ…それでも押し込む！",
			"効果は薄いが、怯まない！"
		};
		return lines[GetRand(2)];
	}
	// リスク承知の積み技(最優先)
	case CommentarySituation::RiskyBoost:
	{
		static const char* lines[] = {
			"リスクを取ってでも、上を目指す！",
			"勝負に出た…！",
			"賭けに出てきたか！",
			"危険は承知の上…それでも、大きく張った一手だ！"
		};
		return lines[GetRand(3)];
	}
	// 素早さ上昇で逆転
	case CommentarySituation::BoostSpeed:
	{
		static const char* lines[] = {
			"一気に加速した…！",
			"主導権を握り返す！",
			"テンポを変えてきた！"
		};
		return lines[GetRand(2)];
	}
	// 火力を溜める
	case CommentarySituation::BoostOffense:
	{
		static const char* lines[] = {
			"力を溜めている…！",
			"牙を研ぎ澄ませている！",
			"ここから攻勢に転じるつもりか！"
		};
		return lines[GetRand(2)];
	}
	// 守りを固める
	case CommentarySituation::BoostDefense:
	{
		static const char* lines[] = {
			"守りを固めてきた！",
			"じっくり構える構え！",
			"これは長期戦の構えだ！"
		};
		return lines[GetRand(2)];
	}
	// どく・やけど技
	case CommentarySituation::InflictStatusDamage:
	{
		static const char* lines[] = {
			"じわじわと効いてくるぞ…！",
			"厄介な一手を仕込んできた！",
			"ボディブローのように効いてくる！"
		};
		return lines[GetRand(2)];
	}
	// まひ技
	case CommentarySituation::InflictParalysis:
	{
		static const char* lines[] = {
			"動きを封じにきた！",
			"自由を奪う一手…！",
			"これは嫌な効果だ！"
		};
		return lines[GetRand(2)];
	}
	// 能力低下技
	case CommentarySituation::Debuff:
	{
		static const char* lines[] = {
			"勢いを削ぎにいく一手！",
			"流れを断ち切る一手だ！",
			"力を奪いにいく作戦だ！"
		};
		return lines[GetRand(2)];
	}
	// 特筆すべき点なし(反応コメント無し)
	default:
	{
		static const char* lines[] = {
			"さあ、次の一手は…！",
			"動き出した…！"
		};
		return lines[GetRand(1)];
	}
	}
}