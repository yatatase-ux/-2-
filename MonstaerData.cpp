#include "MonsterData.h"

const MonsterBaseData MonsterData::monster[] = {
	{ 1, "普通の犬", {Type::Normal, Type::None},  100,  50, 100,  50, 100, 100, {0, -1, -1, -1 }},
	{ 2, "草原の犬", {Type::Grass,  Type::None},  100,  50, 100,  50, 100, 100, {1, -1, -1, -1 }},
	{ 3, "焼き犬",   {Type::Fire,   Type::None},  100,  50, 100,  50, 100, 100, {2, -1, -1, -1 }},
	{ 4, "濡れ犬",   {Type::Water,  Type::None},  100,  50, 100,  50, 100, 100, {3, -1, -1, -1 }},
	{ 5, "脳筋犬",   {Type::Fire,   Type::Water},  70, 100,  50, 100,  50, 105, {0,  1,  2,  3 }},
	{ 6, "堅守犬",   {Type::Normal, Type::None},  200,  20, 150,  20, 150,  60, {0, -1, -1, -1 }},

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


// 正式怪獣保管場所
/*
// 火属性：アタッカー寄り。攻撃つよい
{ , "火物理", {Type::Fire  , Type::None},   80, 120,  65,  50,  65, 100, {0, -1, -1, -1 } // 480
{ , "火特殊", {Type::Fire  , Type::None},   75,  50,  65, 120,  75,  95, {0, -1, -1, -1 } // 480
{ , "火高速", {Type::Fire  , Type::None},   65,  90,  55,  90,  55, 130, {0, -1, -1, -1 } // 485
{ , "火耐久", {Type::Fire  , Type::None},  105,  75, 105,  75,  95,  45, {0, -1, -1, -1 } // 500

// 水属性：耐久寄り。回復とか
{ , "水物理", {Type::Water , Type::None},  90, 110,  85,  55,  90,  70, {0, -1, -1, -1 } // 500
{ , "水特殊", {Type::Water , Type::None},  85,  50,  80, 115,  95,  75, {0, -1, -1, -1 } // 500
{ , "水高速", {Type::Water , Type::None},  75,  85,  70,  85,  70, 120, {0, -1, -1, -1 } // 505
{ , "水耐久", {Type::Water , Type::None}, 110,  65, 105,  70, 110,  40, {0, -1, -1, -1 } // 500

// 技が優秀。状態異常とか能力変化とか
{ , "草物理", {Type::Grass , Type::None},  85, 105,  80,  50,  85,  75, {0, -1, -1, -1 } // 480
{ , "草特殊", {Type::Grass , Type::None},  80,  45,  75, 110,  90,  80, {0, -1, -1, -1 } // 480
{ , "草高速", {Type::Grass , Type::None},  70,  80,  65,  80,  70, 125, {0, -1, -1, -1 } // 490
{ , "草耐久", {Type::Grass , Type::None}, 100,  60,  95,  75, 110,  55, {0, -1, -1, -1 } // 495

// 無属性。技等シンプルな反面、能力値で多少のアドバンテージ
{ , "無物理", {Type::Normal, Type::None},  85, 115,  85,  50,  95,  90, {0, -1, -1, -1 } // 520
{ , "無特殊", {Type::Normal, Type::None},  95,  50,  85, 115,  85,  90, {0, -1, -1, -1 } // 520
{ , "無高速", {Type::Normal, Type::None},  75,  95,  70,  95,  70, 120, {0, -1, -1, -1 } // 525
{ , "無耐久", {Type::Normal, Type::None}, 100,  70, 100,  70, 100,  60, {0, -1, -1, -1 } // 500

*/