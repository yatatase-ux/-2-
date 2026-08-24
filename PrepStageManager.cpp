#include "PrepStageManager.h"

PrepStageManager::PrepStageManager(Cursor* arg_cursor, InputManager* arg_input, PrepContext* arg_context)
	: cursor(arg_cursor), input(arg_input), context(arg_context)
{
	prepStage = std::make_unique<PrepStageBase>(cursor, input, context);
}

void PrepStageManager::Input()
{
	prepStage->Input();
}

bool PrepStageManager::Update()
{
	prepStage->Update();

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