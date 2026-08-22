#pragma once
#pragma once

struct MoveScoreDebug
{
	int moveID = -1;
	int score = 0;
};

struct SwitchScoreDebug
{
	const char* name = "---"; // 追加:未使用スロットでも安全な文字列を指す
	int score = 0;
};