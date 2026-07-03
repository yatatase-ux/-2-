#include "Function.h"
int GetMouseIntX()
{
	IntXY pos;

	GetMousePoint(&pos.x, &pos.y);

	return pos.x;
}
int GetMouseIntY()
{
	IntXY pos;

	GetMousePoint(&pos.x, &pos.y);

	return pos.y;
}

FloatXY GetMousePosFloat()
{
	FloatXY pos;

	pos.x = GetMouseIntX();
	pos.y = GetMouseIntY();

	return pos;
}

float GetFloat2Distance(FloatXY pos1, FloatXY pos2)
{
	float x = pos1.x - pos2.x;
	float y = pos1.y - pos2.y;
	float distance = sqrtf(x * x + y * y);
	return distance;
}

bool CheckCircleHit(FloatXY circle1, float radius1, FloatXY circle2, float radius2)
{
	float distance = GetFloat2Distance(circle1, circle2);
	float radius = radius1 + radius2;
	if (distance <= radius) {
		return true;
	}
	return false;
}

void DrawCenterText(float x, float y, const char* text, unsigned int color, float size)
{
	SetFontSize(size);

	int GT_s = strlen(text);

	int GT_w = GetDrawStringWidth(text, GT_s);

	float draw_x = x - (float)GT_w / 2.0f;
	float draw_y = y - (float)size / 2.0f;

	DrawStringF(draw_x, draw_y, text, color);
}