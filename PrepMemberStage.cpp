#include "PrepMemberStage.h"

PREP_CONSTRUCTOR(PrepMemberStage)
{
	// コンストラクタの実装
}

PREP_INPUT(PrepMemberStage)
{
	if (DEBUG_ALLOW_BACK_TO_HOME && input->Mouse().Push(MOUSE_RIGHT))
	{
		return PrepState::ToHome;
	}
	return PrepState::None;
}

PREP_UPDATE(PrepMemberStage)
{
	// Updateメソッドの実装
	return PrepState::None;
}

void PrepMemberStage::Draw()
{
	// Drawメソッドの実装
	DrawCenterText(WINDOW_W / 2, WINDOW_H / 2, "Member", GetColor(255, 255, 255), 50);
}

void PrepMemberStage::Sound()
{
	// Soundメソッドの実装
}