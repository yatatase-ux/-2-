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
			return PrepState::None;
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
			return PrepState::None;
		}
	}

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