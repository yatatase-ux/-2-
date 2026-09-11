#include "EndBattlePhase.h"

PHASE_CONSTRUCTOR(EndBattlePhase)
{

}

PhaseState EndBattlePhase::Input()
{
	return PhaseState::NONE;
}

PhaseState EndBattlePhase::Update()
{
	if (input->Mouse().Push(MOUSE_LEFT))
	{
		return PhaseState::ToPrep;
	}
	if (input->Mouse().Push(MOUSE_RIGHT))
	{
		return PhaseState::ToEnd;
	}
	return PhaseState::NONE;
}

void EndBattlePhase::Draw()
{
	if (context->isPlayerWin)
	{
		DrawCenterText(WINDOW_W / 2, WINDOW_H / 2, "WIN", GetColor(255, 255, 255), 50);
	}
	else
	{
		DrawCenterText(WINDOW_W / 2, WINDOW_H / 2, "LOSE", GetColor(255, 255, 255), 50);
	}
}

void EndBattlePhase::Sound()
{

}