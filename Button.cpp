// Button.cpp
#include "Button.h"

/// <summary>
/// ボタンのコンストラクタ(円形)
/// </summary>
Button::Button(float x, float y, float r, const char* label,
	unsigned int normalColor, unsigned int hoverColor)
	: pos{ x, y }, radius(r), isCircle(true), label(label),
	normalColor(normalColor), hoverColor(hoverColor), currentColor(normalColor)
{
}

/// <summary>
/// ボタンのコンストラクタ(四角形)
/// </summary>
Button::Button(float x, float y, float w, float h, const char* label,
	unsigned int normalColor, unsigned int hoverColor)
	: pos{ x, y }, width(w), height(h), isCircle(false), label(label),
	normalColor(normalColor), hoverColor(hoverColor), currentColor(normalColor)
{
}

/// <summary>
/// ボタンの無効化設定
/// </summary>
void Button::SetDisabled(bool value, unsigned int disabledColorArg)
{
	disabled = value;
	disabledColor = disabledColorArg;
}

/// <summary>
/// カーソルがボタン上にあるかどうかを判定する
/// </summary>
bool Button::IsHovered(Cursor* cursor)
{
	if (isCircle)
	{
		return CheckCircleHit(pos, radius, cursor->GetPos(), 10.0f);
	}
	return CheckPointBoxHit(cursor->GetPos(), pos, { width, height });
}

/// <summary>
/// ボタンの選択状態を設定する
/// </summary>
void Button::SetSelected(bool value, unsigned int selectedColorArg)
{
	selected = value;
	selectedColor = selectedColorArg;
}

/// <summary>
/// ボタンの入力処理
/// </summary>
bool Button::Input(Cursor* cursor, InputManager* input)
{
	if (disabled) return false;
	return IsHovered(cursor) && input->Mouse().Push(MOUSE_LEFT);
}

/// <summary>
/// ボタンの状態を更新する
/// </summary>
void Button::Update(Cursor* cursor)
{
	if (disabled)
	{
		currentColor = disabledColor;
		return;
	}
	if (selected) // 選択中は色を固定
	{
		currentColor = selectedColor;
		return;
	}
	currentColor = IsHovered(cursor) ? hoverColor : normalColor;
}

/// <summary>
/// ボタンを描画する
/// </summary>
void Button::Draw()
{
	float centerX, centerY;

	if (isCircle)
	{
		DrawCircleAA(pos.x, pos.y, radius, 100, currentColor, 1);
		centerX = pos.x;
		centerY = pos.y;
	}
	else
	{
		DrawFillBox(pos.x, pos.y, pos.x + width, pos.y + height, currentColor);
		centerX = pos.x + width / 2.0f;
		centerY = pos.y + height / 2.0f;
	}

	if (label[0] != '\0')
	{
		DrawCenterText(centerX, centerY, label, GetColor(255, 255, 255), 20.0f); // フォントサイズは仮
	}
}