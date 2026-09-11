#include "MonsterData.h"

const MonsterBaseData MonsterData::monster[] = {
// 火属性：アタッカー寄り。攻撃つよい
{  1, "メラドン",     {Type::Fire  , Type::None},  80, 120,  65,  50,  65, 100, { 1,  2,  5, 21 }, "data/Monster/1-2.png", "data/Monster/1-1.png"}, // 480 火炎斬り/業火拳/闘志/紅葉打ち
{  2, "イフリータ",   {Type::Fire  , Type::None},  75,  50,  65, 120,  75,  95, { 3,  4,  5, 22 }, "data/Monster/2-2.png", "data/Monster/2-1.png"}, // 480 火炎放射/ひのこ/闘志/紅蓮の葉
{  3, "ボルテクモ",   {Type::Fire  , Type::None},  65,  90,  55,  90,  55, 130, { 1, 20, 21,  4 }, "data/Monster/3-2.png", "data/Monster/3-1.png"}, // 485 火炎斬り/気合い十分/紅葉打ち/ひのこ(両刀寄り)
{  4, "マグマドン",   {Type::Fire  , Type::None}, 105,  75, 105,  75,  95,  45, { 2, 27,  5, 21 }, "data/Monster/4-2.png", "data/Monster/4-1.png"}, // 500 業火拳/火花/闘志/紅葉打ち

// 水属性：耐久寄り。回復とか
{  5, "ドトウガル",   {Type::Water , Type::None},  90, 110,  85,  55,  90,  70, { 6,  7, 10, 23 }, "data/Monster/5-2.png", "data/Monster/5-1.png"}, // 500 怒涛の一撃/冷たい牙/守りの霧/熱湯拳
{  6, "ラプラーシャ", {Type::Water , Type::None},  85,  50,  80, 115,  95,  75, { 8,  9, 10, 24 }, "data/Monster/6-2.png", "data/Monster/6-1.png"}, // 500 みずでっぽう/波動水/守りの霧/熱湯
{  7, "ハヤセ",       {Type::Water , Type::None},  75,  85,  70,  85,  70, 120, { 6,  8, 23,  7 }, "data/Monster/7-2.png", "data/Monster/7-1.png"}, // 505 怒涛の一撃/みずでっぽう/熱湯拳/冷たい牙
{  8, "フカミガメ",   {Type::Water , Type::None}, 110,  65, 105,  70, 110,  40, { 7, 28, 10, 24 }, "data/Monster/8-2.png", "data/Monster/8-1.png"}, // 500 冷たい牙/波飛沫/守りの霧/熱湯

// 草属性：技が優秀。状態異常とか能力変化とか
{  9, "ツタマル",     {Type::Grass , Type::None},  85, 105,  80,  50,  85,  75, {11, 13, 15, 25 }, "data/Monster/9-2.png", "data/Monster/9-1.png"}, // 480 つるのムチ/どくの花粉/からみつく/樹液流し
{ 10, "ハナミコ",     {Type::Grass , Type::None},  80,  45,  75, 110,  90,  80, {12, 13, 14, 26 }, "data/Monster/10-2.png", "data/Monster/10-1.png"}, // 480 このは/どくの花粉/しびれ粉/森の雫
{ 11, "カザハヤ",     {Type::Grass , Type::None},  70,  80,  65,  80,  70, 125, {11, 12, 15, 25 }, "data/Monster/11-2.png", "data/Monster/11-1.png"}, // 490 つるのムチ/このは/からみつく/樹液流し
{ 12, "モリオウ",     {Type::Grass , Type::None}, 100,  60,  95,  75, 110,  55, {13, 14, 15, 29 }, "data/Monster/12-2.png", "data/Monster/12-1.png"}, // 495 どくの花粉/しびれ粉/からみつく/葉打ち

// 無属性：技等シンプルな反面、能力値で多少のアドバンテージ
{ 13, "ケンジュウ",   {Type::Normal, Type::None},  85, 115,  85,  50,  95,  90, {16, 17, 20, 19 }, "data/Monster/13-2.png", "data/Monster/13-1.png"}, // 520 渾身の一撃/頭突き/気合い十分/鳴き声
{ 14, "マボロシ",     {Type::Normal, Type::None},  95,  50,  85, 115,  85,  90, {18, 19, 20, 17 }, "data/Monster/14-2.png", "data/Monster/14-1.png"}, // 520  闘気弾/鳴き声/気合い十分/頭突き
{ 15, "カゲロウ",     {Type::Normal, Type::None},  75,  95,  70,  95,  70, 120, {16, 17, 18, 20 }, "data/Monster/15-2.png", "data/Monster/15-1.png"}, // 525 渾身の一撃/頭突き/闘気弾/気合い十分(先制持ちの器用万能)
{ 16, "イワジュウ",   {Type::Normal, Type::None}, 100,  70, 100,  70, 100,  60, {17, 19, 20, 30 }, "data/Monster/16-2.png", "data/Monster/16-1.png"}, // 500 頭突き/鳴き声/気合い十分/神速の一撃

//{ 17, "デバッグ用つよつよお爺さん", {Type::Fire, Type::Water}, 200, 250, 200, 200, 200, 200, {1, 8, 11, 0 }}, // 1250

};
const int  MonsterData::MonsterSize = sizeof(monster) / sizeof(MonsterBaseData);

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

int MonsterData::GetCount()
{
    return MonsterSize;
}

const MonsterBaseData& MonsterData::GetByIndex(int index)
{
    return monster[index];
}

void MonsterData::LoadImages()
{
    for (int i = 0; i < MonsterSize; i++)
    {
        monster[i].ImageLoad(); // constなImageLoadなので、constな配列要素からでも呼び出せる
    }
}