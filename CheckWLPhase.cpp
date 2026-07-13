#include "CheckWLPhase.h"

CheckWLPhase::CheckWLPhase(Cursor* arg_cursor, Members* arg_members, BattleContext* arg_context, InputManager* arg_input)
	: PhaseBase(arg_cursor, arg_members, arg_context, arg_input)
{

}

PhaseState CheckWLPhase::Input()
{
	return PhaseState::NONE;
}

PhaseState CheckWLPhase::Update()
{
	return PhaseState::NONE;
}

void CheckWLPhase::Draw()
{
	DrawString(500, 250, "Dead Monster", GetColor(255, 255, 255));
}

void CheckWLPhase::Sound()
{

}
