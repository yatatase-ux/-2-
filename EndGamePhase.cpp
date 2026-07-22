#include "EndBattlePhase.h"

PHASE_CONSTRUCTOR(EndGamePhase)
{

}

PhaseState EndGamePhase::Input()
{
	return PhaseState::NONE;
}

PhaseState EndGamePhase::Update()
{
	return PhaseState::NONE;
}

void EndGamePhase::Draw()
{
	DrawCenterText(WINDOW_W / 2, WINDOW_H / 2, "WIN", GetColor(255, 255, 255), 50);
}

void EndGamePhase::Sound()
{

}