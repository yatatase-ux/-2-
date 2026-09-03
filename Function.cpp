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

/// <summary>
/// 中央揃えで文字列を描画する関数
/// </summary>
/// <param name="x">X座標</param>
/// <param name="y">Y座標</param>
/// <param name="text">描画する文字列</param>
/// <param name="color">文字色</param>
/// <param name="size">文字サイズ</param>
void DrawCenterText(float x, float y, const char* text, unsigned int color, float size)
{
	SetFontSize(size);

	int GT_s = strlen(text);

	int GT_w = GetDrawStringWidth(text, GT_s);

	float draw_x = x - (float)GT_w / 2.0f;
	float draw_y = y - (float)size / 2.0f;

	DrawStringF(draw_x, draw_y, text, color);
}

/// <summary>
/// 中央揃えで文字列と変数を描画する関数
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
/// <param name="color"></param>
/// <param name="size"></param>
/// <param name="format"></param>
/// <param name=""></param>
void DrawCenterFormatText(float x, float y, unsigned int color, float size, const char* format, ...)
{
	char buffer[256]; // 描画する文字列の一時バッファ

	va_list args;
	va_start(args, format);
	vsprintf_s(buffer, sizeof(buffer), format, args); // formatと可変長引数から文字列を組み立てる
	va_end(args);

	SetFontSize(size);
	int GT_s = strlen(buffer);
	int GT_w = GetDrawStringWidth(buffer, GT_s);
	float draw_x = x - (float)GT_w / 2.0f;
	float draw_y = y - size / 2.0f;
	DrawStringF(draw_x, draw_y, buffer, color);
}

/// <summary>
/// 左揃えで文字列を描画する関数
/// </summary>
/// <param name="x">X座標(文字列の左端)</param>
/// <param name="y">Y座標(文字列の垂直方向の中心。DrawCenterTextと合わせてある)</param>
/// <param name="text">描画する文字列</param>
/// <param name="color">文字色</param>
/// <param name="size">文字サイズ</param>
void DrawLeftText(float x, float y, const char* text, unsigned int color, float size)
{
	SetFontSize(size);
	float draw_y = y - size / 2.0f;
	DrawStringF(x, draw_y, text, color);
}

/// <summary>
/// 左揃えで文字列と変数を描画する関数
/// </summary>
/// <param name="x">X座標(文字列の左端)</param>
/// <param name="y">Y座標(文字列の垂直方向の中心)</param>
/// <param name="color">文字色</param>
/// <param name="size">文字サイズ</param>
/// <param name="format">書式指定文字列</param>
void DrawLeftFormatText(float x, float y, unsigned int color, float size, const char* format, ...)
{
	char buffer[256];
	va_list args;
	va_start(args, format);
	vsprintf_s(buffer, sizeof(buffer), format, args);
	va_end(args);

	SetFontSize(size);
	float draw_y = y - size / 2.0f;
	DrawStringF(x, draw_y, buffer, color);
}

/// <summary>
/// 右揃えで文字列を描画する関数
/// </summary>
/// <param name="x">X座標(文字列の右端)</param>
/// <param name="y">Y座標(文字列の垂直方向の中心。DrawCenterTextと合わせてある)</param>
/// <param name="text">描画する文字列</param>
/// <param name="color">文字色</param>
/// <param name="size">文字サイズ</param>
void DrawRightText(float x, float y, const char* text, unsigned int color, float size)
{
	SetFontSize(size);
	int GT_s = strlen(text);
	int GT_w = GetDrawStringWidth(text, GT_s);
	float draw_x = x - (float)GT_w; // 右端がxに来るよう、文字列の幅ぶん左にずらす
	float draw_y = y - size / 2.0f;
	DrawStringF(draw_x, draw_y, text, color);
}

/// <summary>
/// 右揃えで文字列と変数を描画する関数
/// </summary>
/// <param name="x">X座標(文字列の右端)</param>
/// <param name="y">Y座標(文字列の垂直方向の中心)</param>
/// <param name="color">文字色</param>
/// <param name="size">文字サイズ</param>
/// <param name="format">書式指定文字列</param>
void DrawRightFormatText(float x, float y, unsigned int color, float size, const char* format, ...)
{
	char buffer[256];
	va_list args;
	va_start(args, format);
	vsprintf_s(buffer, sizeof(buffer), format, args);
	va_end(args);

	SetFontSize(size);
	int GT_s = strlen(buffer);
	int GT_w = GetDrawStringWidth(buffer, GT_s);
	float draw_x = x - (float)GT_w;
	float draw_y = y - size / 2.0f;
	DrawStringF(draw_x, draw_y, buffer, color);
}

//---------------------------------------------------------------------------------
//	点と円の当たり判定（座標に Float2 を渡すバージョン）
//---------------------------------------------------------------------------------
bool CheckPointCircleHit(FloatXY point, FloatXY circle, float radius)
{
	float distance = GetFloat2Distance(point, circle);
	if (distance <= radius) {
		return true;
	}
	return false;
}
//---------------------------------------------------------------------------------
//	点と四角の当たり判定（座標と大きさに Float2 を渡すバージョン）
//---------------------------------------------------------------------------------
bool CheckPointBoxHit(FloatXY point, FloatXY box_pos, FloatXY box_size)
{
	if (point.x >= box_pos.x && point.x <= box_pos.x + box_size.x) {
		if (point.y >= box_pos.y && point.y <= box_pos.y + box_size.y) {
			return true;
		}
	}
	return false;
}
//---------------------------------------------------------------------------------
//	円と四角の当たり判定（座標と大きさに Float2 を渡すバージョン）
//---------------------------------------------------------------------------------
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

/// <summary>
/// 値を割合に変換し、ステータスバー(黄色の矩形)を描画する関数
/// </summary>
/// <param name="x">バー左端のX座標</param>
/// <param name="y">バー上端のY座標</param>
/// <param name="maxWidth">バーの最大幅</param>
/// <param name="value">現在の値</param>
/// <param name="maxValue">基準となる最大値</param>
void DrawStatBar(float x, float y, float maxWidth, int value, int maxValue)
{
	float ratio = (float)value / maxValue;
	if (ratio > 1.0f) ratio = 1.0f; // 極端な値でも枠からはみ出さないようクランプ
	float width = maxWidth * ratio;
	DrawFillBox((int)x, (int)y, (int)(x + width), (int)(y + 20.0f), GetColor(255, 255, 0));
}