#include "PrepMemberStage.h"
#include "Config.h" // DEBUG_ALLOW_BACK_TO_HOME, DEBUG_SHOW_CPU_SELECTION
#include "RandomUtil.h"

PREP_CONSTRUCTOR(PrepMemberStage),
partyButtons{
	Button({ 150.0f, 520.0f }, { 130.0f, 130.0f }, "data/button/pMon.png", "", GetColor(100,100,100), GetColor(200,200,0), TRUE),
	Button({ 310.0f, 520.0f }, { 130.0f, 130.0f }, "data/button/pMon.png", "", GetColor(100,100,100), GetColor(200,200,0), TRUE),
	Button({ 470.0f, 520.0f }, { 130.0f, 130.0f }, "data/button/pMon.png", "", GetColor(100,100,100), GetColor(200,200,0), TRUE),
	Button({ 630.0f, 520.0f }, { 130.0f, 130.0f }, "data/button/pMon.png", "", GetColor(100,100,100), GetColor(200,200,0), TRUE),
	Button({ 790.0f, 520.0f }, { 130.0f, 130.0f }, "data/button/pMon.png", "", GetColor(100,100,100), GetColor(200,200,0), TRUE),
	Button({ 950.0f, 520.0f }, { 130.0f, 130.0f }, "data/button/pMon.png", "", GetColor(100,100,100), GetColor(200,200,0), TRUE)
},
enemyButtons{
	Button({ 150.0f, 150.0f }, { 130.0f, 130.0f }, "data/button/pMon.png", "", GetColor(200,0,0), GetColor(200,0,0), TRUE),
	Button({ 310.0f, 150.0f }, { 130.0f, 130.0f }, "data/button/pMon.png", "", GetColor(200,0,0), GetColor(200,0,0), TRUE),
	Button({ 470.0f, 150.0f }, { 130.0f, 130.0f }, "data/button/pMon.png", "", GetColor(200,0,0), GetColor(200,0,0), TRUE),
	Button({ 630.0f, 150.0f }, { 130.0f, 130.0f }, "data/button/pMon.png", "", GetColor(200,0,0), GetColor(200,0,0), TRUE),
	Button({ 790.0f, 150.0f }, { 130.0f, 130.0f }, "data/button/pMon.png", "", GetColor(200,0,0), GetColor(200,0,0), TRUE),
	Button({ 950.0f, 150.0f }, { 130.0f, 130.0f }, "data/button/pMon.png", "", GetColor(200,0,0), GetColor(200,0,0), TRUE)
},
confirmButton(WINDOW_W / 2.0f, 650.0f, 50.0f, 2.0f,"data/button/start.png", "戦闘開始", GetColor(100, 100, 100), GetColor(0, 200, 0))
{
	for (int i = 0; i < PARTY_MAX; i++) memberOrder[i] = -1;

	// CPUの3体を、既に確定している6体(context->enemyParty)からランダム選出
	int chosenIndices[MEMBER_MAX];
	PickRandomDistinct(PARTY_MAX, MEMBER_MAX, chosenIndices);

	for (int i = 0; i < MEMBER_MAX; i++)
	{
		context->eBattle[i] = context->enemyParty.mons[chosenIndices[i]];
		context->eMember.mons[i] = &context->eBattle[i];
	}
	context->eMember.current = 0;

	if (DEBUG_SHOW_CPU_SELECTION)
	{
		for (int i = 0; i < MEMBER_MAX; i++)
		{
			enemyButtons[chosenIndices[i]].SetSelected(true, GetColor(255, 255, 0));
		}
	}

	confirmButton.SetDisabled(true); // 3体揃うまでは押せない

	BG = LoadGraph("data/BG/PrepMenberBG.jpg");
}

PrepMemberStage::~PrepMemberStage()
{
	DeleteGraph(BG);
}

PREP_INPUT(PrepMemberStage)
{
	DetailInput();

	for (int i = 0; i < PARTY_MAX; i++)
	{
		if (partyButtons[i].Input(cursor, input))
		{
			if (memberOrder[i] >= 0)
			{
				int removedOrder = memberOrder[i];
				memberOrder[i] = -1;
				partyButtons[i].SetSelected(false);
				for (int j = 0; j < PARTY_MAX; j++)
				{
					if (memberOrder[j] > removedOrder) memberOrder[j]--;
				}
				selectedCount--;
			}
			else if (selectedCount < MEMBER_MAX)
			{
				memberOrder[i] = selectedCount;
				partyButtons[i].SetSelected(true);
				selectedCount++;
			}

			confirmButton.SetDisabled(selectedCount != MEMBER_MAX);
			return PrepState::None;
		}
	}

	if (confirmButton.Input(cursor, input))
	{
		for (int i = 0; i < PARTY_MAX; i++)
		{
			if (memberOrder[i] >= 0)
			{
				context->pMember.mons[memberOrder[i]] = &context->playerParty->mons[i];
			}
		}
		context->pMember.current = 0;
		return PrepState::Complete;
	}

	if (DEBUG_ALLOW_BACK_TO_HOME && input->Mouse().Push(MOUSE_RIGHT))
	{
		return PrepState::ToHome;
	}

	return PrepState::None;
}

PREP_UPDATE(PrepMemberStage)
{
	for (int i = 0; i < PARTY_MAX; i++)
	{
		partyButtons[i].Update(cursor);
		enemyButtons[i].Update(cursor); // selected状態をcurrentColorに反映させるため必要
	}
	confirmButton.Update(cursor);
	return PrepState::None;
}

void PrepMemberStage::Draw()
{
	DrawExtendGraph(0, 0, WINDOW_W, WINDOW_H, BG, TRUE);

	if (detailTarget != nullptr)
	{
		DrawFillBox(100, 210, WINDOW_W - 100, 452, GetColor(50, 100, 180));
		memberDetail.Draw(*detailTarget, 100.0f, 210.0f); // 座標は仮
	}

	for (int i = 0; i < PARTY_MAX; i++)
	{
		partyButtons[i].Draw();
		const MonsterBaseData* d = context->playerParty->mons[i].data;
		if (d != nullptr)
		{
			int image = d->eImage;
			DrawRotaGraphF(ImagePos[0][i].x, ImagePos[0][i].y, 0.1, 0.0, image, TRUE);
		}
	}
	for (int i = 0; i < PARTY_MAX; i++)
	{
		partyButtons[i].Draw();
		if (memberOrder[i] >= 0)
		{
			FloatXY p = partyButtons[i].GetPos();
			DrawCenterFormatText(p.x, p.y - 90.0f, GetColor(0, 0, 0), 24.0f, "%d", memberOrder[i] + 1);
		}
	}

	for (int i = 0; i < PARTY_MAX; i++)
	{
		enemyButtons[i].Draw();
		DrawRotaGraphF(ImagePos[1][i].x, ImagePos[1][i].y, 0.1, 0.0, context->enemyParty.mons[i].data->eImage, TRUE);
		
	}

	confirmButton.Draw();
}

void PrepMemberStage::Sound()
{
}

PrepState PrepMemberStage::DetailInput()
{
	// SHIFTを押している間は、詳細表示の切り替えだけを行う(通常の選択操作はさせない)
	if (input->Key().Check(SHIFT))
	{
		// プレイヤー側6体をチェック
		for (int i = 0; i < PARTY_MAX; i++)
		{
			const MonsterBaseData* candidate = context->playerParty->mons[i].data;
			if (candidate == nullptr) continue; // 空枠は対象外

			if (partyButtons[i].Input(cursor, input)) // ここで初めてPushが呼ばれ、正しくクリックを検出する
			{
				// トグル:今表示中の対象と同じなら閉じる、違えば切り替える
				detailTarget = (detailTarget == candidate) ? nullptr : candidate;
				return PrepState::None;
			}
		}

		// CPU側6体をチェック
		for (int i = 0; i < PARTY_MAX; i++)
		{
			const MonsterBaseData* candidate = context->enemyParty.mons[i].data;
			if (enemyButtons[i].Input(cursor, input))
			{
				detailTarget = (detailTarget == candidate) ? nullptr : candidate;
				return PrepState::None;
			}
		}

		return PrepState::None; // SHIFT押下中は、以降の通常選択処理には進ませない
	}
}