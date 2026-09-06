#pragma once
#include "PhaseBase.h"
#include "Button.h"
#include "MonsterDetail.h"
#include "MoveDetail.h"
#include "BattleHUD.h"
#include "EffectApplier.h"

class ChangeMonsPhase : public PhaseBase
{
protected:

	Button buttons[3];

	MonsterDetail monsterDetail;
	MoveDetail moveDetail;
	int detailIndex = -1;       // -1:非表示。0〜2なら交代候補の詳細を表示中
	bool showingMoveDetail = false;
	int detailMoveID = -1;

	const FloatXY detailBoxStart = { 50.0f, 50.0f };
	const FloatXY detailBoxEnd = { 900.0f, 650.0f };

	BattleHUD battleHUD;

	EffectApplier effect;

	bool showWarning = false; // 警告文表示
	int warningTimer = 0;     // 表示時間

public:

	PHASE_CLASS(ChangeMonsPhase);

};