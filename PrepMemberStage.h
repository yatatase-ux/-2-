#pragma once
#include "PrepStageBase.h"
#include "Button.h"

class PrepMemberStage : public PrepStageBase
{
private:

	int memberOrder[PARTY_MAX];		// 各パーティ枠が何番目に選ばれたか(-1:未選択)
	int selectedCount = 0;			// 選択済みの数(0～3)
	Button partyButtons[PARTY_MAX];	// 自分の6体
	Button enemyButtons[PARTY_MAX]; // CPUの6体(表示のみ)
	Button confirmButton;			// 戦闘開始ボタン

public:
	PREP_CLASS(PrepMemberStage);
	bool CursorInParty(int index);
	bool CursorInConfirm();
	bool IsChosenForBattle(int enemyPartyIndex);
};