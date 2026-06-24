#pragma once
#include <DxLib.h>
#include "Structure.h"
#include "Cursor.h"

const int BUTTOM_MAX = 2;

class ButtleUI
{
protected:

	enum
	{
		Fight,
		Change
	};
	FloatCircle buttom[BUTTOM_MAX];

	Cursor* cursor = nullptr;

public:

	ButtleUI(Cursor* arg_cursor = nullptr);

	void Update();

	void Draw();

	bool CursorInButtom(int type);

	void ChangeButtomColor(int type, bool InFlag);
};


