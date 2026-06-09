#include "MonsterData.h"

void MonsterData::ShowData()
{
	DrawFormatString(20,  20, GetColor(0, 0, 0), "Name : %s", monster.Name);
	DrawFormatString(20,  40, GetColor(0, 0, 0), "PATK : %d", monster.PATK);
	DrawFormatString(20,  60, GetColor(0, 0, 0), "PDEF : %d", monster.PDEF);
	DrawFormatString(20,  80, GetColor(0, 0, 0), "MATK : %d", monster.MATK);
	DrawFormatString(20, 100, GetColor(0, 0, 0), "MDEF : %d", monster.MDEF);
	DrawFormatString(20, 120, GetColor(0, 0, 0), "SPD  : %d", monster.SPD);
}