#include "PrepPartyStage.h"

PREP_CONSTRUCTOR(PrepPartyStage)
{
	// 下段:パーティ6枠。持ち越し済みのパーティ内容をラベルに反映
	for (int i = 0; i < PARTY_MAX; i++)
	{
		float x = 150.0f + i * 160.0f;
		float y = 620.0f;
		const MonsterBaseData* d = context->playerParty->mons[i].data;
		const char* label = (d != nullptr) ? d->Name : "空";
		slotButtons[i] = Button(x, y, 60.0f, label, GetColor(100, 100, 100), GetColor(200, 200, 0));
	}

	// 上段:選択可能な怪獣一覧
	const int columns = 6;
	rosterButtons.reserve(MonsterData::GetCount());
	for (int i = 0; i < MonsterData::GetCount(); i++)
	{
		int row = i / columns;
		int col = i % columns;
		float x = 150.0f + col * 160.0f;
		float y = 100.0f + row * 130.0f;
		rosterButtons.emplace_back(x, y, 50.0f, MonsterData::GetByIndex(i).Name, GetColor(150, 150, 150), GetColor(200, 200, 0));
	}
}

PREP_INPUT(PrepPartyStage)
{
	if (showingDetail)
	{
		ShowMoveDetail();
		return PrepState::None; // 詳細表示中は、これ以降には絶対に進ませない
	}

	if (input->Key().Check(SHIFT))
	{
		ShowMonsterDetail();
		return PrepState::None; // SHIFT押下中も、通常操作はさせない
	}

	DefaultInput();

	if (input->Mouse().Push(MOUSE_RIGHT))
	{
		return PrepState::ToHome;
	}

	return PrepState::None;
}

PREP_UPDATE(PrepPartyStage)
{
	for (int i = 0; i < PARTY_MAX; i++)
	{
		slotButtons[i].Update(cursor);
	}
	for (int i = 0; i < (int)rosterButtons.size(); i++)
	{
		rosterButtons[i].Update(cursor);
	}
	return PrepState::None;
}

void PrepPartyStage::Draw()
{
	DrawCenterText(WINDOW_W / 2, 40, "Party", GetColor(255, 255, 255), 40.0f);

	for (int i = 0; i < PARTY_MAX; i++)
	{
		slotButtons[i].Draw();
	}
	for (int i = 0; i < (int)rosterButtons.size(); i++)
	{
		rosterButtons[i].Draw();
	}

	// 詳細表示中は、最後に上書きするように描画する(常に一番手前に見えるように)
	if (showingDetail && detailTarget != nullptr)
	{
		// 半透明の黒で背景を覆う
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 180);
		DrawBox(0, 0, WINDOW_W, WINDOW_H, GetColor(0, 0, 0), TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		DrawFillBox(detailBoxStart.x, detailBoxStart.y, detailBoxEnd.x, detailBoxEnd.y, GetColor(128, 128, 128));
		monsterDetail.Draw(*detailTarget, detailBoxStart.x, detailBoxStart.y, 
								detailBoxEnd.x, detailBoxEnd.y);

		if (showingMoveDetail)
		{
			// 技詳細をさらに上に重ねて表示
//			DrawFillBox(200, 200, 980, 500, GetColor(220, 220, 220));
			moveDetail.Draw(MoveTable[detailMoveID], 200.0f, 200.0f, 980.0f, 500.0f);
		}
	}
}

void PrepPartyStage::Sound()
{
}

bool PrepPartyStage::IsAlreadyInParty(const MonsterBaseData* mons)
{
	for (int i = 0; i < PARTY_MAX; i++)
	{
		if (i == selectedSlot) continue;
		if (context->playerParty->mons[i].data == mons) return true;
	}
	return false;
}

void PrepPartyStage::TrySwap(int slotIndex, int rosterIndex)
{
	const MonsterBaseData* chosen = &MonsterData::GetByIndex(rosterIndex);

	selectedSlot = slotIndex; // IsAlreadyInPartyが対象枠を除外できるよう先にセット
	if (!IsAlreadyInParty(chosen))
	{
		context->playerParty->mons[slotIndex].data = chosen;
		context->playerParty->mons[slotIndex].CurrentHP = chosen->HP;
		slotButtons[slotIndex].SetLabel(chosen->Name); // 追加:ラベルを更新
	}

	slotButtons[slotIndex].SetSelected(false);
	rosterButtons[rosterIndex].SetSelected(false);

	selectedSlot = -1;
	selectedRosterIndex = -1;
}

void PrepPartyStage::DefaultInput()
{
	// 以下、これまで通りの通常操作(枠選択・怪獣選択・入れ替え)
	for (int i = 0; i < PARTY_MAX; i++)
	{
		if (slotButtons[i].Input(cursor, input))
		{
			if (selectedRosterIndex >= 0)
			{
				TrySwap(i, selectedRosterIndex);
			}
			else
			{
				if (selectedSlot >= 0) slotButtons[selectedSlot].SetSelected(false);
				selectedSlot = i;
				slotButtons[i].SetSelected(true);
			}
		}
	}

	for (int i = 0; i < (int)rosterButtons.size(); i++)
	{
		if (rosterButtons[i].Input(cursor, input))
		{
			if (selectedSlot >= 0)
			{
				TrySwap(selectedSlot, i);
			}
			else
			{
				if (selectedRosterIndex >= 0) rosterButtons[selectedRosterIndex].SetSelected(false);
				selectedRosterIndex = i;
				rosterButtons[i].SetSelected(true);
			}
		}
	}
}

void PrepPartyStage::ShowMonsterDetail()
{
	// (if (input->Key().Check(SHIFT)) は削除。呼び出し元で既に判定済みのため)
	for (int i = 0; i < (int)rosterButtons.size(); i++)
	{
		if (rosterButtons[i].Input(cursor, input))
		{
			showingDetail = true;
			detailTarget = &MonsterData::GetByIndex(i);
			return; // 1つ見つかったら十分
		}
	}
}

void PrepPartyStage::ShowMoveDetail()
{
	// (if (showingDetail) は削除。呼び出し元で既に判定済みのため)
	if (input->Mouse().Push(MOUSE_RIGHT))
	{
		if (showingMoveDetail)
		{
			showingMoveDetail = false;
		}
		else
		{
			showingDetail = false;
			detailTarget = nullptr;
		}
		return;
	}

	if (!showingMoveDetail && input->Mouse().Push(MOUSE_LEFT))
	{
		for (int i = 0; i < MOVE_SLOT_MAX; i++)
		{
			FloatXY boxPos, boxSize;
			if (monsterDetail.GetMoveBoxRect(i, detailBoxStart.x, detailBoxStart.y, detailBoxEnd.x, detailBoxEnd.y, boxPos, boxSize))
			{
				if (CheckPointBoxHit(cursor->GetPos(), boxPos, boxSize))
				{
					int moveID = detailTarget->MoveID[i];
					if (moveID >= 0)
					{
						detailMoveID = moveID;
						showingMoveDetail = true;
					}
					break;
				}
			}
		}
	}
}