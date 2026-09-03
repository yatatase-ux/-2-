#include "PrepMemberStage.h"
#include "Config.h" // DEBUG_ALLOW_BACK_TO_HOME, DEBUG_SHOW_CPU_SELECTION
#include "RandomUtil.h"

PREP_CONSTRUCTOR(PrepMemberStage),
partyButtons{
	Button(150.0f, 500.0f, 60.0f, context->playerParty->mons[0].data->Name, GetColor(100,100,100), GetColor(200,200,0)),
	Button(310.0f, 500.0f, 60.0f, context->playerParty->mons[1].data->Name, GetColor(100,100,100), GetColor(200,200,0)),
	Button(470.0f, 500.0f, 60.0f, context->playerParty->mons[2].data->Name, GetColor(100,100,100), GetColor(200,200,0)),
	Button(630.0f, 500.0f, 60.0f, context->playerParty->mons[3].data->Name, GetColor(100,100,100), GetColor(200,200,0)),
	Button(790.0f, 500.0f, 60.0f, context->playerParty->mons[4].data->Name, GetColor(100,100,100), GetColor(200,200,0)),
	Button(950.0f, 500.0f, 60.0f, context->playerParty->mons[5].data->Name, GetColor(100,100,100), GetColor(200,200,0))
},
enemyButtons{
	Button(150.0f, 150.0f, 50.0f, context->enemyParty.mons[0].data->Name, GetColor(200,0,0), GetColor(200,0,0)),
	Button(310.0f, 150.0f, 50.0f, context->enemyParty.mons[1].data->Name, GetColor(200,0,0), GetColor(200,0,0)),
	Button(470.0f, 150.0f, 50.0f, context->enemyParty.mons[2].data->Name, GetColor(200,0,0), GetColor(200,0,0)),
	Button(630.0f, 150.0f, 50.0f, context->enemyParty.mons[3].data->Name, GetColor(200,0,0), GetColor(200,0,0)),
	Button(790.0f, 150.0f, 50.0f, context->enemyParty.mons[4].data->Name, GetColor(200,0,0), GetColor(200,0,0)),
	Button(950.0f, 150.0f, 50.0f, context->enemyParty.mons[5].data->Name, GetColor(200,0,0), GetColor(200,0,0))
},
confirmButton(WINDOW_W / 2.0f, 650.0f, 50.0f, "戦闘開始", GetColor(100, 100, 100), GetColor(0, 200, 0))
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
}

PREP_INPUT(PrepMemberStage)
{
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
	DrawCenterText(WINDOW_W / 2, 40, "Member", GetColor(255, 255, 255), 40.0f);

	for (int i = 0; i < PARTY_MAX; i++)
	{
		partyButtons[i].Draw();
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
	}
	confirmButton.Draw();
}

void PrepMemberStage::Sound()
{
}