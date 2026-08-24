#include "PrepStageManager.h"

PrepStageManager::PrepStageManager()
{
	prepStage = std::make_unique<PrepStageBase>();
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