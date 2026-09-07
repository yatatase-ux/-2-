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
	DrawExtendGraphF(pos.x, pos.y, pos.x + size, pos.y + size, image, TRUE);
}

void Cursor::Sound()
{

}

FloatXY Cursor::GetPos()
{
	return pos;
}