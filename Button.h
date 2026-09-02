#pragma once
#include "Structure.h" // FloatXY・FloatCircle の定義に必要
#include "DxLib.h"
#include "Cursor.h"
#include "InputManager.h"

class Button
{
private:
	FloatXY pos;       // Vector2 ではなく FloatXY が正しい型名
	float radius = 0.0f;
	float width = 0.0f;
	float height = 0.0f;
	bool isCircle;
	const char* label;
	unsigned int normalColor;
	unsigned int hoverColor;
	unsigned int disabledColor = 0;
	unsigned int currentColor;
	bool disabled = false;

	unsigned int selectedColor = 0;
	bool selected = false;

public:
	Button() = default;
	Button(float x, float y, float r, const char* label,
		unsigned int normalColor, unsigned int hoverColor);
	Button(float x, float y, float w, float h, const char* label,
		unsigned int normalColor, unsigned int hoverColor);

	void SetDisabled(bool value, unsigned int disabledColorArg = GetColor(100, 100, 100));
	bool IsHovered(Cursor* cursor);
	void SetSelected(bool value, unsigned int selectedColorArg = GetColor(255, 255, 0));
	void SetLabel(const char* newLabel) { label = newLabel; }

	bool Input(Cursor* cursor, InputManager* input);
	void Update(Cursor* cursor);
	void Draw();

	FloatXY GetPos() const { return pos; } // 補足表示など、外部から位置を使いたい場合のため
};