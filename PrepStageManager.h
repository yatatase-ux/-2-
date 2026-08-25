#pragma once
#include "PrepStageBase.h"
#include "Cursor.h"
#include "InputManager.h"
#include "PrepContext.h"
#include "BattleContext.h"
#include <memory>

enum class PrepStep 
{	
	SelectParty,
	SelectMembers 
};

class PrepStageManager
{
private:

	Cursor* cursor;
	InputManager* input;
	BattleContext* context;

	std::unique_ptr<PrepStageBase> prepStage;
	PrepStep step = PrepStep::SelectParty;

public:

	PrepStageManager(Cursor* arg_cursor, InputManager* arg_input, BattleContext* arg_context);
	void Input();
	bool Update();
	void Draw();
	void Sound();

};