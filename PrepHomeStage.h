#pragma once
#include "PrepStageBase.h"

enum
{
	BtnParty,
	BtnMember,

	HOME_BUTTON_MAX
};

class PrepHomeStage : public PrepStageBase
{
private:
	FloatCircle button[HOME_BUTTON_MAX];
public:
	PREP_CLASS(PrepHomeStage);
	bool CursorInButton(int type);
	void ChangeButtonColor(int type, bool inFlag);
};