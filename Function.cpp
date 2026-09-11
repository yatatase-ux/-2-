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
/// <param name="color">色</param>
void DrawStatBar(float x, float y, float maxWidth, int value, int maxValue, unsigned int color)
{
	float ratio = (float)value / maxValue;
	if (ratio > 1.0f) ratio = 1.0f;
	if (ratio < 0.0f) ratio = 0.0f;
	float width = maxWidth * ratio;
	DrawFillBox((int)x, (int)y, (int)(x + width), (int)(y + 20.0f), color);
}

void DrawCenterBox(FloatXY pos, FloatXY size, unsigned int color, bool flag, float LineSize)
{
	float sX = pos.x - size.x / 2.0f;
	float sY = pos.y - size.y / 2.0f;
	float eX = sX + size.x;
	float eY = sY + size.y;

	DrawBoxAA((int)sX, (int)sY, (int)eX, (int)eY, color, flag, LineSize);

}

/// <summary>
/// 指定した縦の範囲に、基準色を軸にした上下グラデーションを、段階的な帯で描く
/// </summary>
/// <param name="yStart">範囲の開始Y座標</param>
/// <param name="yEnd">範囲の終了Y座標</param>
/// <param name="baseR">基準色の赤成分(0~255)</param>
/// <param name="baseG">基準色の緑成分(0~255)</param>
/// <param name="baseB">基準色の青成分(0~255)</param>
/// <param name="steps">帯の数(多いほど滑らかに、少ないほどドット絵らしい段差に)</param>
void DrawGradientRegion(int yStart, int yEnd, int baseR, int baseG, int baseB, int steps)
{
	int height = yEnd - yStart;
	if (height <= 0 || steps <= 0) return;

	int bandHeight = height / steps;
	if (bandHeight <= 0) bandHeight = 1;

	for (int i = 0; i < steps; i++)
	{
		float t = (steps > 1) ? (float)i / (steps - 1) : 0.0f; // 0.0(最初の帯)〜1.0(最後の帯)
		float factor = 1.3f - 0.6f * t;

		int r = (int)(baseR * factor);
		int g = (int)(baseG * factor);
		int b = (int)(baseB * factor);
		if (r > 255) r = 255; if (r < 0) r = 0;
		if (g > 255) g = 255; if (g < 0) g = 0;
		if (b > 255) b = 255; if (b < 0) b = 0;

		int bandStart = yStart + i * bandHeight;
		int bandEnd = (i == steps - 1) ? yEnd : bandStart + bandHeight; // 最後の帯は端数も含めて端まで埋める

		DrawFillBox(0, bandStart, WINDOW_W, bandEnd, GetColor(r, g, b));
	}
}