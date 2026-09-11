#include "Button.h"
#include "Function.h"

/// <summary>
/// ボタンのコンストラクタ(円形)
/// </summary>
Button::Button(float x, float y, float r, float s, const char* imagePath, const char* label,
	unsigned int normalColor, unsigned int hoverColor)
	: pos{ x, y }, radius(r), size(s), image(LoadGraph(imagePath)), isCircle(true), label(label),
	normalColor(normalColor), hoverColor(hoverColor), currentColor(normalColor)
{
}

/// <summary>
/// ボタンのコンストラクタ(四角形)
/// </summary>
Button::Button(FloatXY p, FloatXY s, const char* imagePath, const char* label,
	unsigned int normalColor, unsigned int hoverColor, bool Flag)
	: pos(p),boxSize(s), image(LoadGraph(imagePath)), isCircle(false), label(label),
	normalColor(normalColor), hoverColor(hoverColor), currentColor(normalColor), centerFlag(Flag)
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
	if (centerFlag)
	{
		// posは中心なので、左上を逆算してから判定する
		FloatXY topLeft = { pos.x - boxSize.x / 2.0f, pos.y - boxSize.y / 2.0f };
		return CheckPointBoxHit(cursor->GetPos(), topLeft, boxSize);
	}
	return CheckPointBoxHit(cursor->GetPos(), pos, boxSize);
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

		DrawRotaGraphF(pos.x, pos.y, size, 0.0, image, 1);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 180);
		DrawCircleAA(pos.x, pos.y, radius, 100, currentColor, 1);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		centerX = pos.x;
		centerY = pos.y;
	}
	else
	{
		if (centerFlag)
		{
			DrawCenterBox(pos, boxSize, currentColor, FALSE, 3.0f);
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 180);
			DrawCenterBox(pos , boxSize, currentColor, FALSE, 3.0f);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			centerX = pos.x;
			centerY = pos.y;
		}
		else 
		{
			DrawExtendGraphF(pos.x, pos.y, pos.x + boxSize.x, pos.y + boxSize.y, image, TRUE);
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 180);
			DrawFillBox(pos.x, pos.y, pos.x + boxSize.x, pos.y + boxSize.y, currentColor);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			centerX = pos.x + boxSize.x / 2.0f;
			centerY = pos.y + boxSize.y / 2.0f;
		}
	}

	if (label[0] != '\0')
	{
		DrawCenterText(centerX, centerY, label, GetColor(0, 0, 0), 20.0f);
	}
}