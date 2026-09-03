#pragma once
#include "CommentarySituation.h"

struct CommentaryLineEntry
{
	CommentarySituation situation;
	bool cpuIsEarlyer;
	bool hit;
	const char* text;
};

extern const CommentaryLineEntry CommentaryLines[];
extern const int CommentaryLineCount;