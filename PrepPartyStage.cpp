#include "PrepPartyStage.h"

PREP_CONSTRUCTOR(PrepPartyStage)
{
	// 下段:パーティ6枠を横並びに配置
	for (int i = 0; i < PARTY_MAX; i++)
	{
		slotButtons[i] = { 150.0f + i * 160.0f, 620.0f, 60.0f, GetColor(100,100,100) };
	}

	// 上段:選択可能な怪獣を格子状に配置(1行6体想定、要調整)
	const int columns = 6;
	rosterButtons.resize(MonsterData::GetCount());
	for (int i = 0; i < MonsterData::GetCount(); i++)
	{
		int row = i / columns;
		int col = i % columns;
		rosterButtons[i] = { 150.0f + col * 160.0f, 100.0f + row * 130.0f, 50.0f, GetColor(150,150,150) };
	}
}

PREP_INPUT(PrepPartyStage)
{
	if (input->Mouse().Push(MOUSE_LEFT))
	{
		// パーティ枠をクリック
		for (int i = 0; i < PARTY_MAX; i++)
		{
			if (CursorInSlot(i))
			{
				if (selectedRosterIndex >= 0)
					TrySwap(i, selectedRosterIndex); // 怪獣→枠の順で選んでいた場合、ここで確定
				else
					selectedSlot = i; // 枠だけ選択(選び直しも兼ねる)
				return PrepState::None;
			}
		}

		// 怪獣一覧をクリック
		for (int i = 0; i < MonsterData::GetCount(); i++)
		{
			if (CursorInRoster(i))
			{
				if (selectedSlot >= 0)
					TrySwap(selectedSlot, i); // 枠→怪獣の順で選んでいた場合、ここで確定
				else
					selectedRosterIndex = i; // 怪獣だけ選択(選び直しも兼ねる)
				return PrepState::None;
			}
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
		bool isSelected = (i == selectedSlot);
		slotButtons[i].color = isSelected ? GetColor(255, 255, 0)
			: CursorInSlot(i) ? GetColor(200, 200, 0)
			: GetColor(100, 100, 100);
	}
	for (int i = 0; i < MonsterData::GetCount(); i++)
	{
		bool isSelected = (i == selectedRosterIndex);
		rosterButtons[i].color = isSelected ? GetColor(255, 255, 0)
			: CursorInRoster(i) ? GetColor(200, 200, 0)
			: GetColor(150, 150, 150);
	}
	return PrepState::None;
}

void PrepPartyStage::Draw()
{
	DrawCenterText(WINDOW_W / 2, 40, "Party", GetColor(255, 255, 255), 40.0f);

	// パーティ枠(中身の名前 or 「空」)
	for (int i = 0; i < PARTY_MAX; i++)
	{
		DrawCircleAA(slotButtons[i].pos.x, slotButtons[i].pos.y, slotButtons[i].r, 100, slotButtons[i].color, 1);

		const MonsterBaseData* d = context->playerParty->mons[i].data;
		const char* label = (d != nullptr) ? d->Name : "空";
		DrawCenterText(slotButtons[i].pos.x, slotButtons[i].pos.y, label, GetColor(0, 0, 0), 18.0f);
	}

	// 選択可能な怪獣一覧
	for (int i = 0; i < MonsterData::GetCount(); i++)
	{
		DrawCircleAA(rosterButtons[i].pos.x, rosterButtons[i].pos.y, rosterButtons[i].r, 100, rosterButtons[i].color, 1);
		DrawCenterText(rosterButtons[i].pos.x, rosterButtons[i].pos.y, MonsterData::GetByIndex(i).Name, GetColor(0, 0, 0), 16.0f);
	}
}

void PrepPartyStage::Sound()
{
}

bool PrepPartyStage::CursorInSlot(int index)
{
	return CheckCircleHit(slotButtons[index].pos, slotButtons[index].r, cursor->GetPos(), 10.0f);
}

bool PrepPartyStage::CursorInRoster(int index)
{
	return CheckCircleHit(rosterButtons[index].pos, rosterButtons[index].r, cursor->GetPos(), 10.0f);
}

bool PrepPartyStage::IsAlreadyInParty(const MonsterBaseData* mons)
{
	for (int i = 0; i < PARTY_MAX; i++)
	{
		if (i == selectedSlot) continue; // 今入れ替えようとしている枠自身は比較しない
		if (context->playerParty->mons[i].data == mons) return true;
	}
	return false;
}

void PrepPartyStage::TrySwap(int slotIndex, int rosterIndex)
{
	const MonsterBaseData* chosen = &MonsterData::GetByIndex(rosterIndex);

	selectedSlot = slotIndex; // IsAlreadyInPartyが「今の対象枠」を除外できるよう、先にセット
	if (!IsAlreadyInParty(chosen))
	{
		context->playerParty->mons[slotIndex].data = chosen;
		context->playerParty->mons[slotIndex].CurrentHP = chosen->HP;
	}
	// 重複していた場合は何もしない(将来的にはNG演出を追加)

	selectedSlot = -1;
	selectedRosterIndex = -1; // 両方リセットして次の選択に備える
}