#include "PrepHomeStage.h"

PREP_CONSTRUCTOR(PrepHomeStage)
{

}

PREP_INPUT(PrepHomeStage)
{

}

PREP_UPDATE(PrepHomeStage)
{
	return PrepState::None;
}

void PrepHomeStage::Draw()
{
	DrawCenterText(WINDOW_W / 2, WINDOW_H / 2, "HOME", GetColor(255, 255, 255), 50);
}

void PrepHomeStage::Sound()
{

}