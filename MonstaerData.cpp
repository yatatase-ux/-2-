#include "MonsterData.h"

const BasicState MonsterData::monster[] = {
	{ 1, "モンスター", {Element::Fire, Element::NONE}, 108, 130, 95, 80, 85, 102 },
	{ 2, "創造神", {Element::Fire, Element::NONE}, 120, 120, 120, 120, 120, 120 },
	{ 3, "ひわまり", {Element::Holy, Element::Earth}, 30, 30, 30, 30, 30, 30}
};
const int  MonsterData::MonsterSize = sizeof(monster) / sizeof(BasicState);

void MonsterData::ShowData()
{
	for (int i = 0; i < MonsterSize; i++) {
		DrawFormatString(20 * (i + 1) * 10, 20, GetColor(0, 0, 0), "Name : %s", monster[i].Name);
		DrawFormatString(20 * (i + 1) * 10, 40, GetColor(0, 0, 0), "PATK : %d", monster[i].PATK);
		DrawFormatString(20 * (i + 1) * 10, 60, GetColor(0, 0, 0), "PDEF : %d", monster[i].PDEF);
		DrawFormatString(20 * (i + 1) * 10, 80, GetColor(0, 0, 0), "MATK : %d", monster[i].MATK);
		DrawFormatString(20 * (i + 1) * 10, 100, GetColor(0, 0, 0), "MDEF : %d", monster[i].MDEF);
		DrawFormatString(20 * (i + 1) * 10, 120, GetColor(0, 0, 0), "SPD  : %d", monster[i].SPD);
	}
}