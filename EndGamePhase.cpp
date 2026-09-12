#include "EndBattlePhase.h"
#include "Function.h"

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
		DrawGradientRegion(0, WINDOW_H, 255, 210, 60, 20); // –¾‚é‚¢‹àFŒn(j•ŸŠ´)
		DrawCenterText(WINDOW_W / 2, WINDOW_H / 2, "WIN", GetColor(0, 0, 0), 50);
	}
	else
	{
		DrawGradientRegion(0, WINDOW_H, 60, 60, 90, 20);   // —‚¿’…‚¢‚½®FŒn(Ã‚©‚È—]‰C)
		DrawCenterText(WINDOW_W / 2, WINDOW_H / 2, "LOSE", GetColor(255, 255, 255), 50);
	}
}

void EndBattlePhase::Sound()
{

}