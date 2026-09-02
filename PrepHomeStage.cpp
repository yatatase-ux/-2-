#include "PrepHomeStage.h"

PREP_CONSTRUCTOR(PrepHomeStage),
	partyButton(WINDOW_W / 4,	   WINDOW_H / 2, 150.0f, "パーティ", GetColor(175, 0, 0), GetColor(255, 255, 0)),
	memberButton(WINDOW_W / 4 * 3, WINDOW_H / 2, 150.0f, "戦闘", GetColor(0, 175, 0), GetColor(255, 255, 0))
{
	memberButton.SetDisabled(!IsPartyFull()); // コンストラクタ時点でも反映(1フレーム目対策)
}

PREP_INPUT(PrepHomeStage)
{
	if (partyButton.Input(cursor, input)) return PrepState::ToParty;
	if (memberButton.Input(cursor, input)) return PrepState::ToMember;

	// 揃っていない状態でメンバーボタンを押そうとしたら警告
	if (!IsPartyFull() && memberButton.IsHovered(cursor) && input->Mouse().Push(MOUSE_LEFT))
	{
		showWarning = true;
		warningTimer = 120;
	}

	return PrepState::None;
}

PREP_UPDATE(PrepHomeStage)
{
	memberButton.SetDisabled(!IsPartyFull());
	partyButton.Update(cursor);
	memberButton.Update(cursor);

	if (warningTimer > 0)
	{
		warningTimer--;
		if (warningTimer <= 0) showWarning = false;
	}

	return PrepState::None;
}

void PrepHomeStage::Draw()
{
	partyButton.Draw();
	memberButton.Draw();

	if (showWarning)
	{
		int w = 220;
		DrawFillBox (w, 350, WINDOW_W - w, 450, GetColor(255, 255, 0));
		DrawCenterText(WINDOW_W / 2, 400, "パーティが6体揃っていません！", GetColor(255, 0, 0), 50.0f);
	}
}

void PrepHomeStage::Sound()
{

}

bool PrepHomeStage::IsPartyFull()
{
	for (int i = 0; i < PARTY_MAX; i++)
	{
		if (context->playerParty->mons[i].data == nullptr) return false;
	}
	return true;
}