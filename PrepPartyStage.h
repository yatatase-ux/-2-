#pragma once
#include "PrepStageBase.h"
#include "MonsterData.h"
#include <vector>
#include "Button.h"

class PrepPartyStage : public PrepStageBase
{
private:
	int selectedSlot = -1;					// 選択中のパーティ枠(-1:未選択)
	int selectedRosterIndex = -1;			// 選択中の怪獣(-1:未選択)
	Button slotButtons[PARTY_MAX];		// 下段:パーティ6枠
	std::vector<Button> rosterButtons; // 上段:選択可能な怪獣一覧

	bool IsAlreadyInParty(const MonsterBaseData* mons);
	void TrySwap(int slotIndex, int rosterIndex);

public:

	PREP_CLASS(PrepPartyStage);
};