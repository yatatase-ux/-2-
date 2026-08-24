#pragma once
#include "PrepStageBase.h"
#include "memory"

class PrepStageManager
{
private:

	std::unique_ptr<PrepStageBase> prepStage;

public:

	PrepStageManager();
	void Input();
	bool Update();
	void Draw();
	void Sound();

}

