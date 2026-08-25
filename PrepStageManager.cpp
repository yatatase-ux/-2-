#include "PrepStageManager.h"
#include "PrepPartyStage.h"
#include "PrepMemberStage.h"
#include "PrepHomeStage.h"

PrepStageManager::PrepStageManager(Cursor* arg_cursor, InputManager* arg_input, BattleContext* arg_context)
	: cursor(arg_cursor), input(arg_input), context(arg_context)
{
	prepStage = std::make_unique<PrepHomeStage>(cursor, input, context);
}

bool PrepStageManager::Input()
{
	PrepState state = prepStage->Input(); // Input‚ÌŒ‹‰Ê‚ðŒ©‚é
	return HandleTransition(state);
}

bool PrepStageManager::Update()
{
	PrepState state = prepStage->Update(); // Update‚ÌŒ‹‰Ê‚ðŒ©‚é
	return HandleTransition(state);
}

bool PrepStageManager::HandleTransition(PrepState state)
{
	switch (state)
	{
	case PrepState::ToHome:
		prepStage = std::make_unique<PrepHomeStage>(cursor, input, context);
		break;
	case PrepState::ToParty:
		prepStage = std::make_unique<PrepPartyStage>(cursor, input, context);
		break;
	case PrepState::ToMember:
		prepStage = std::make_unique<PrepMemberStage>(cursor, input, context);
		break;
	case PrepState::Complete:
		return true;
	default:
		break;
	}
	return false;
}

void PrepStageManager::Draw()
{
	prepStage->Draw();
}

void PrepStageManager::Sound()
{
	prepStage->Sound();
}

