#pragma once
#include "PrepStageBase.h"
#include "MonsterData.h"
#include <vector>
#include "Button.h"
#include "MonsterDetail.h"
#include "MoveDetail.h"

class PrepPartyStage : public PrepStageBase
{
private:
	int selectedSlot = -1;					// 選択中のパーティ枠(-1:未選択)
	int selectedRosterIndex = -1;			// 選択中の怪獣(-1:未選択)
	Button slotButtons[PARTY_MAX];		// 下段:パーティ6枠
	std::vector<Button> rosterButtons; // 上段:選択可能な怪獣一覧

	bool IsAlreadyInParty(const MonsterBaseData* mons);
	void TrySwap(int slotIndex, int rosterIndex);

	const FloatXY detailBoxStart = { 100.0f, 50.0f };
	const FloatXY detailBoxEnd = { WINDOW_W - 100.0f, WINDOW_H - 50.0f };

	MonsterDetail monsterDetail;
	bool showingDetail = false;
	const MonsterBaseData* detailTarget = nullptr;

	MoveDetail moveDetail;
	bool showingMoveDetail = false;
	int detailMoveID = -1;

	void DefaultInput();
	void ShowMonsterDetail();
	void ShowMoveDetail();

public:

	PREP_CLASS(PrepPartyStage);
};