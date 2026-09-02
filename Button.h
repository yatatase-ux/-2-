#pragma once
#include "DxLib.h"
#include "Cursor.h"
#include "InputManager.h"

class Button
{
private:

	FloatCircle shape;
	const char* label;
	unsigned int normalColor;
	unsigned int hoverColor;
	unsigned int currentColor;

	bool IsHovered(Cursor* cursor);

public:

	Button(float x, float y, float r, const char* label,
		unsigned int normalColor, unsigned int hoverColor);

	bool Input(Cursor* cursor, InputManager* input); // クリックされたらtrue
	void Update(Cursor* cursor);                      // ホバー中かどうかで色を更新
	void Draw();

};