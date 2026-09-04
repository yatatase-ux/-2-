#pragma once
#include "MoveData.h"
#include "Function.h"
#include "Structure.h"

class MoveDetail
{
public:

	void Draw(const MoveData& move, float x, float y, float width, float height);

	void DrawEffect(const MoveData& move, float x, float y, FloatXY bSize, float effectSize);
};