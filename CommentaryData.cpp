#include "CommentaryData.h"

const CommentaryLineEntry CommentaryLines[] =
{
	{ CommentarySituation::StayReadingSwitch, true, true, "見事読み的中だ！これは痛い！" },
	{ CommentarySituation::StayReadingSwitch, true, true, "読み通りだ、この一撃は重い！" },
	{ CommentarySituation::StayReadingSwitch, true, true, "完璧に決まった、読みの勝利だ！" },

	{ CommentarySituation::StayReadingSwitch, true, false, "しかし予想は外れる！この読みを上手くかわしました！" },
	{ CommentarySituation::StayReadingSwitch, true, false, "読みは外れたか…うまく回避された！" },
	{ CommentarySituation::StayReadingSwitch, true, false, "これは読み切れなかったか…！" },

	{ CommentarySituation::StayReadingSwitch, false, true, "CPUこれを読んでいた！大ダメージだ！" },
	{ CommentarySituation::StayReadingSwitch, false, true, "読み通りの展開…見事な一撃だ！" },
	{ CommentarySituation::StayReadingSwitch, false, true, "予測が的中、痛烈な一撃！" },

	{ CommentarySituation::StayReadingSwitch, false, false, "プレイヤー上手く合わせました！CPUはこれを読んでいたか…！？" },
	{ CommentarySituation::StayReadingSwitch, false, false, "しかし読みは外れる…予想外の一手だ！" },
	{ CommentarySituation::StayReadingSwitch, false, false, "これは意表を突かれたか…！" },

	{ CommentarySituation::SwitchAvoidingThreat, true, true, "しかしこれは痛くないでしょう。CPU見事に合わせました！" },
	{ CommentarySituation::SwitchAvoidingThreat, true, true, "読み通りの技…だが、もう効かない！" },
	{ CommentarySituation::SwitchAvoidingThreat, true, true, "見切っていた、この程度では崩れない！" },

	{ CommentarySituation::SwitchAvoidingThreat, true, false, "これはプレイヤーがうまく読みました！CPU、これは痛いダメージとなりました！" },
	{ CommentarySituation::SwitchAvoidingThreat, true, false, "まさかの展開…読みが外れてしまった！" },
	{ CommentarySituation::SwitchAvoidingThreat, true, false, "これは予想外だ…手痛い一撃！" },

	{ CommentarySituation::SwitchAvoidingThreat, false, true, "相性不利と見て交代！これが功を奏した！" },
	{ CommentarySituation::SwitchAvoidingThreat, false, true, "読み通りの入れ替え、見事に決まった！" },
	{ CommentarySituation::SwitchAvoidingThreat, false, true, "この判断が生きた、絶妙なタイミングだ！" },

	{ CommentarySituation::SwitchAvoidingThreat, false, false, "相性を見て交代したが、プレイヤーはそれを上回った…！" },
	{ CommentarySituation::SwitchAvoidingThreat, false, false, "しかし読みが外れる…厳しい展開だ！" },
	{ CommentarySituation::SwitchAvoidingThreat, false, false, "この交代は裏目に出たか…！" },
};
const int CommentaryLineCount = sizeof(CommentaryLines) / sizeof(CommentaryLineEntry);