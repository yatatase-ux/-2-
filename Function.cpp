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

bool CheckPointCircleHit(FloatXY point, FloatXY circle, float radius)
{
	float distance = GetFloat2Distance(point, circle);
	if (distance <= radius) {
		return true;
	}
	return false;
}

bool CheckCircleBoxHit(FloatXY circle, float radius, FloatXY box_pos, FloatXY box_size)
{
	FloatXY near_pos;

	near_pos.x = circle.x;
	if (near_pos.x < box_pos.x)				near_pos.x = box_pos.x;
	if (near_pos.x > box_pos.x + box_size.x)	near_pos.x = box_pos.x + box_size.x;

	near_pos.y = circle.y;
	if (near_pos.y < box_pos.y)				near_pos.y = box_pos.y;
	if (near_pos.y > box_pos.y + box_size.y)	near_pos.y = box_pos.y + box_size.y;

	if (CheckPointCircleHit(near_pos, circle, radius)) {
		return true;
	}

	return false;
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