#include "Button.h"

Button::Button(float x, float y, float r, const char* label,
	unsigned int normalColor, unsigned int hoverColor)
	: shape{ x, y, r, normalColor }, label(label),
	normalColor(normalColor), hoverColor(hoverColor), currentColor(normalColor)
{

}

bool Button::IsHovered(Cursor* cursor)
{
	return CheckCircleHit(shape.pos, shape.r, cursor->GetPos(), 10.0f);
}

bool Button::Input(Cursor* cursor, InputManager* input)
{
	return IsHovered(cursor) && input->Mouse().Push(MOUSE_LEFT);
}

void Button::Update(Cursor* cursor)
{
	currentColor = IsHovered(cursor) ? hoverColor : normalColor;
}

void Button::Draw()
{
	DrawCircleAA(shape.pos.x, shape.pos.y, shape.r, 100, currentColor, 1);
	if (label[0] != '\0')
	{
		DrawCenterText(shape.pos.x, shape.pos.y, label, GetColor(255, 255, 255), 20.0f); // フォントサイズは仮
	}
}