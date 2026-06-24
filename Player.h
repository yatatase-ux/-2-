#pragma once
#include <DxLib.h>
#include "Cursor.h"
#include <memory>

class Player
{
protected:

	std::unique_ptr<Cursor> cursor;

public:

	Player();

	void Input();

	void Update();

	void Draw();

	void Sound();

	Cursor* GetCursor() const;
};

