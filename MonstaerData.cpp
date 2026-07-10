#include "MonsterData.h"

const MonsterBaseData MonsterData::monster[] = {
	{ 1, "•’Ê‚ÌŒ¢", {Type::Normal, Type::None}, 100, 10, 100, 10, 100, 100, {0, -1, -1, -1 }},
	{ 2, "‘Œ´‚ÌŒ¢", {Type::Grass,  Type::None}, 100, 10, 100, 10, 100, 100, {1, -1, -1, -1 }},
	{ 3, "Ä‚«Œ¢",   {Type::Fire,   Type::None}, 100, 10, 100, 10, 100, 100, {2, -1, -1, -1 }},
	{ 4, "”G‚êŒ¢",   {Type::Water,  Type::None}, 100, 10, 100, 10, 100, 100, {3, -1, -1, -1 }},

};
const int  MonsterData::MonsterSize = sizeof(monster) / sizeof(MonsterBaseData);

//void MonsterData::ShowData()
//{
//	for (int i = 0; i < MonsterSize; i++) {
//		DrawFormatString(20 * (i + 1) * 10, 20, GetColor(0, 0, 0), "Name : %s", monster[i].Name);
//		DrawFormatString(20 * (i + 1) * 10, 40, GetColor(0, 0, 0), "PATK : %d", monster[i].PATK);
//		DrawFormatString(20 * (i + 1) * 10, 60, GetColor(0, 0, 0), "PDEF : %d", monster[i].PDEF);
//		DrawFormatString(20 * (i + 1) * 10, 80, GetColor(0, 0, 0), "MATK : %d", monster[i].MATK);
//		DrawFormatString(20 * (i + 1) * 10, 100, GetColor(0, 0, 0), "MDEF : %d", monster[i].MDEF);
//		DrawFormatString(20 * (i + 1) * 10, 120, GetColor(0, 0, 0), "SPD  : %d", monster[i].SPD);
//	}
//}

const MonsterBaseData* MonsterData::FindByID(int id)
{
    for (int i = 0; i < MonsterSize; i++)
    {
        if (monster[i].ID == id)
        {
            return &monster[i];
        }
    }

    return nullptr;
}