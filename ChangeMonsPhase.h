#pragma once
#include "PhaseBase.h"
#include "Button.h"
#include "MonsterDetail.h"

class ChangeMonsPhase : public PhaseBase
{
protected:

	Button buttons[3];

	MonsterDetail monsterDetail;
	int detailIndex = -1; // -1:非表示。0?2ならそのボタン(交代候補)を表示中

public:

	PHASE_CLASS(ChangeMonsPhase);

};