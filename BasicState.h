#pragma once

enum Element
{
	NONE, 	// –³
	NORMAL,	// –³‘®«
	Fire,	// ‰Î
	Water,	// …
	Wind,	// •—
	Earth,	// “y
	Holy,	// Œõ
	Dark,	// ˆÅ
};

enum Move
{
	NONE,
	Tackle
};

struct BasicState
{
	int ID;
	const char Name[256];
	Element element[2];
	int HP;
	int PATK;
	int PDEF;
	int MATK;
	int MDEF;
	int SPD;
	Move move[4];
};
