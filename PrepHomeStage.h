#pragma once
#include "PrepStageBase.h"
#include "Button.h"

enum
{
	BtnParty,
	BtnMember,

	HOME_BUTTON_MAX
};

class PrepHomeStage : public PrepStageBase
{
private:

	Button partyButton;
	Button memberButton;
	bool showWarning = false;
	int warningTimer = 0;

	bool IsPartyFull();

public:

	PREP_CLASS(PrepHomeStage);

};