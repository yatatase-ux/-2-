#pragma once
#include "PrepStageBase.h"

class PrepMemberStage : public PrepStageBase
{
private:

	int memberOrder[PARTY_MAX]; // 各パーティ枠が何番目に選ばれたか(-1:未選択)
	bool selected[PARTY_MAX] = { false };
	int selectedCount = 0;
	FloatCircle partyButtons[PARTY_MAX];   // 自分の6体(選択可能)
	FloatCircle enemyButtons[PARTY_MAX];   // CPUの6体(表示のみ)
	FloatCircle confirmButton;             // 戦闘開始ボタン

public:
	PREP_CLASS(PrepMemberStage);
	bool CursorInParty(int index);
	bool CursorInConfirm();
	bool IsChosenForBattle(int enemyPartyIndex);
};