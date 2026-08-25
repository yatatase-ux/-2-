#include "PrepPartyStage.h"

PREP_CONSTRUCTOR(PrepPartyStage)
{
	// コンストラクタの実装
}

PREP_INPUT(PrepPartyStage)
{
	// Inputメソッドの実装
	if (input->Mouse().Push(MOUSE_RIGHT))
	{
		return PrepState::ToHome;
	}

	return PrepState::None;
}

PREP_UPDATE(PrepPartyStage)
{
	// Updateメソッドの実装
	return PrepState::None;
}

void PrepPartyStage::Draw()
{
	// Drawメソッドの実装

	DrawCenterText(WINDOW_W / 2, WINDOW_H / 2, "Party", GetColor(255, 255, 255), 50);
}

void PrepPartyStage::Sound()
{
	// Soundメソッドの実装
}