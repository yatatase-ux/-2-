#pragma once
#include "Structure.h"
#include <cmath>

int GetMouseIntX();
int GetMouseIntY();

FloatXY GetMousePosFloat();

float GetFloat2Distance(FloatXY pos1, FloatXY pos2);

bool CheckCircleHit(FloatXY circle1, float radius1, FloatXY circle2, float radius2);