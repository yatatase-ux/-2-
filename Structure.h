#pragma once
#include <DxLib.h>

struct IntXY
{
	int x, y;
};

struct FloatXY
{
	float x, y;
};

struct FloatCircle
{
	FloatXY pos;
	float r;
	unsigned int color;
};
