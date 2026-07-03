#pragma once
#include "Structure.h"
#include <cmath>

int GetMouseIntX();
int GetMouseIntY();

// マウスの座標を FloatXY で取得する関数
FloatXY GetMousePosFloat();

float GetFloat2Distance(FloatXY pos1, FloatXY pos2);

bool CheckCircleHit(FloatXY circle1, float radius1, FloatXY circle2, float radius2);

/// <summary>
/// 中央揃えで文字列を描画する関数
/// </summary>
/// <param name="x">X座標</param>
/// <param name="y">Y座標</param>
/// <param name="text">描画する文字列</param>
/// <param name="color">文字色</param>
/// <param name="size">文字サイズ</param>
void DrawCenterText(float x, float y, const char* text, unsigned int color, float size);

//	点と円の当たり判定（座標に Float2 を渡すバージョン）
bool CheckPointCircleHit(FloatXY point, FloatXY circle, float radius);

//	点と四角の当たり判定（座標と大きさに Float2 を渡すバージョン）
bool CheckPointBoxHit(FloatXY point, FloatXY box_pos, FloatXY box_size);

//	円と四角の当たり判定（座標と大きさに Float2 を渡すバージョン）
bool CheckCircleBoxHit(FloatXY circle, float radius, FloatXY box_pos, FloatXY box_size);