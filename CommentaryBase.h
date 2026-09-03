#pragma once
#include "CommentarySituation.h"

struct CommentaryBaseData
{
	CommentarySituation situation;
	bool cpuIsEarlyer; // true:CPU先行時に使う / false:CPU後攻時に使う
	bool hit;          // true:予測的中時 / false:予測外れ時
	const char* text;
};