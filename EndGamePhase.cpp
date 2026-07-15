#include "EndBattlePhase.h"

EndGamePhase::EndGamePhase(Cursor* arg_cursor, Members* arg_pMembers, Members* arg_eMembers, BattleContext* arg_context, InputManager* arg_input)
	:PhaseBase(arg_cursor, arg_pMembers, arg_eMembers, arg_context, arg_input)
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