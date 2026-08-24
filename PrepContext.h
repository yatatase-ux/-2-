#pragma once
#include "Party.h"

struct PrepContext
{
	Party playerParty;   // ①6体選出フェーズが書き込む
	// ②3体選出フェーズが書き込む結果(Membersに変換する前段階のインデックスなど)を、この後追加していく
};