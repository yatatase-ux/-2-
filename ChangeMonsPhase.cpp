#include "ChangeMonsPhase.h"

ChangeMonsPhase::ChangeMonsPhase(Cursor* arg_cursor, BattleContext* arg_context, InputManager* arg_input)
	: PhaseBase(arg_cursor, arg_context, arg_input)
{

}

PhaseState ChangeMonsPhase::Input()
{
	if (input->Mouse().Push(MOUSE_RIGHT)) return PhaseState::COMMAND;

	return PhaseState::NONE;
}

PhaseState ChangeMonsPhase::Update()
{
	return PhaseState::NONE;
}

void ChangeMonsPhase::Draw()
{

}

void ChangeMonsPhase::Sound()
{

}
