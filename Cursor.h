#pragma once
#include <DxLib.h>
#include "Function.h"

class Cursor
{
protected:

	FloatXY pos;

public:

	Cursor();

	void Input();

	void Update();

	void Draw();

	void Sound();

	FloatXY GetPos();
};
