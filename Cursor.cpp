#include "Cursor.h"

Cursor::Cursor()
{
	pos = { GetMousePosFloat() };
}

void Cursor::Input()
{

}

void Cursor::Update()
{
	pos = GetMousePosFloat();
}

void Cursor::Draw()
{
	DrawCircleAA(pos.x, pos.y, 10.0f, 100, GetColor(255, 255, 0), 1);
}

void Cursor::Sound()
{

}

FloatXY Cursor::GetPos()
{
	return pos;
}