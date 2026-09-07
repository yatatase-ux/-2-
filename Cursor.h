#pragma once
#include <DxLib.h>
#include "Function.h"

class Cursor
{
protected:

	FloatXY pos;

	int image = LoadGraph("data/UI/cursor2.png");
	const float size = 40.0f;

public:

	Cursor();

	void Input();
	void Update();
	void Draw();
	void Sound();
	FloatXY GetPos();
};
