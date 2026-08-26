#include "PrepHomeStage.h"

PREP_CONSTRUCTOR(PrepHomeStage)
{
	button[BtnParty] = { 700.0f, 400.0f, 75.0f, GetColor(175,0,0) };
	button[BtnMember] = { 700.0f, 575.0f, 75.0f, GetColor(0,175,0) };
}

PREP_INPUT(PrepHomeStage)
{
	// クリック判定・遷移

	if (input->Mouse().Push(MOUSE_LEFT))
	{
		if (CursorInButton(BtnParty))  return PrepState::ToParty;

		if (CursorInButton(BtnMember))
		{
			bool isPartyFull = true;
			for (int i = 0; i < PARTY_MAX; i++)
			{
				if (context->playerParty.mons[i].data == nullptr) { isPartyFull = false; break; }
			}
			if (isPartyFull) return PrepState::ToMember;
			// 空きがある場合は何もしない(将来的には警告表示などを追加)
		}
	}
	return PrepState::None;
}

PREP_UPDATE(PrepHomeStage)
{
	for (int i = 0; i < HOME_BUTTON_MAX; i++)
	{
		ChangeButtonColor(i, CursorInButton(i));
	}
	return PrepState::None;
}

void PrepHomeStage::Draw()
{
	for (int i = 0; i < HOME_BUTTON_MAX; i++)
	{
		DrawCircleAA(button[i].pos.x, button[i].pos.y, button[i].r, 100, button[i].color, 1);
	}
	DrawCenterText(button[BtnParty].pos.x, button[BtnParty].pos.y, "パーティ", GetColor(255, 255, 255), 24.0f);
	DrawCenterText(button[BtnMember].pos.x, button[BtnMember].pos.y, "戦闘", GetColor(255, 255, 255), 24.0f);
}

void PrepHomeStage::Sound()
{
}

bool PrepHomeStage::CursorInButton(int type)
{
	return CheckCircleHit(button[type].pos, 75.0f, cursor->GetPos(), 10.0f);
}

void PrepHomeStage::ChangeButtonColor(int type, bool inFlag)
{
	button[type].color = inFlag ? GetColor(0, 0, 0) : GetColor(150, 150, 150);
}