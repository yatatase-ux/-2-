#pragma once
#include <DxLib.h>
#include "Structure.h"
#include "Cursor.h"
#include "KeyAction.h"
#include "Enumeration.h"

const int BUTTOM_MAX = 2;

class BattleUI
{
protected:

	
	FloatCircle buttom[BUTTOM_MAX];

	Cursor* cursor = nullptr;

	MouseAct mouse_act;

	bool mouse_input = false;

public:

	BattleUI(Cursor* arg_cursor = nullptr);

	void Input();

	void Update();

	void Draw();

	void Sound();

	bool CursorInButtom(int type);

	void ChangeButtomColor(int type, bool InFlag);

	bool InputButton(int type);
};


