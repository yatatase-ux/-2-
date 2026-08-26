#include "PrepMemberStage.h"
#include "Config.h" // DEBUG_ALLOW_BACK_TO_HOME
#include "MonsterData.h"
#include "RandomUtil.h"

PREP_CONSTRUCTOR(PrepMemberStage)
{
	// プレイヤーのパーティのボタン初期化
	for (int i = 0; i < PARTY_MAX; i++)
	{
		partyButtons[i] = { 150.0f + i * 160.0f, 500.0f, 60.0f, GetColor(100,100,100) };
	}
	// CPUのパーティの初期化
	for (int i = 0; i < PARTY_MAX; i++)
	{
		enemyButtons[i] = { 150.0f + i * 160.0f, 150.0f, 50.0f, GetColor(200,0,0) };
	}
	// 戦闘開始ボタン
	confirmButton = { WINDOW_W / 2.0f, 650.0f, 50.0f, GetColor(100,100,100) };

	// CPUパーティをランダムに3体選出(重複なし)
	int chosenIndices[MEMBER_MAX];
	PickRandomDistinct(PARTY_MAX, MEMBER_MAX, chosenIndices);

	for (int i = 0; i < MEMBER_MAX; i++)
	{
		context->eBattle[i] = context->enemyParty.mons[chosenIndices[i]]; // BattleMonsterごとコピー
		context->eMember.mons[i] = &context->eBattle[i];
	}
	context->eMember.current = 0;
}

PREP_INPUT(PrepMemberStage)
{
	if (input->Mouse().Push(MOUSE_LEFT))
	{
		// 自分のパーティをトグル選択(最大3体まで)
		for (int i = 0; i < PARTY_MAX; i++)
		{
			if (CursorInParty(i))
			{
				if (selected[i])
				{
					selected[i] = false;
					selectedCount--;
				}
				else if (selectedCount < MEMBER_MAX)
				{
					selected[i] = true;
					selectedCount++;
				}
				return PrepState::None;
			}
		}

		// 3体選ばれている時のみ、決定ボタンが機能する
		if (selectedCount == MEMBER_MAX && CursorInConfirm())
		{
			int idx = 0;
			for (int i = 0; i < PARTY_MAX; i++)
			{
				if (selected[i])
				{
					context->pMember.mons[idx] = &context->playerParty->mons[i];
					idx++;
				}
			}
			context->pMember.current = 0;
			return PrepState::Complete;
		}
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
		if (selected[i])
			partyButtons[i].color = GetColor(255, 255, 0);
		else
			partyButtons[i].color = CursorInParty(i) ? GetColor(200, 200, 0) : GetColor(100, 100, 100);
	}
	return PrepState::None;
}

void PrepMemberStage::Draw()
{
	DrawCenterText(WINDOW_W / 2, 40, "Member", GetColor(255, 255, 255), 40.0f);

	// 自分のパーティ6体
	for (int i = 0; i < PARTY_MAX; i++)
	{
		DrawCircleAA(partyButtons[i].pos.x, partyButtons[i].pos.y, partyButtons[i].r, 100, partyButtons[i].color, 1);
		DrawCenterText(partyButtons[i].pos.x, partyButtons[i].pos.y,
			context->playerParty->mons[i].data->Name, GetColor(0, 0, 0), 18.0f);
	}

	// CPU側6体(表示のみ)
	for (int i = 0; i < PARTY_MAX; i++)
	{
		unsigned int color = GetColor(200, 0, 0);
		if (DEBUG_SHOW_CPU_SELECTION && IsChosenForBattle(i))
		{
			color = GetColor(255, 255, 0); // デバッグ用ハイライト
		}
		DrawCircleAA(enemyButtons[i].pos.x, enemyButtons[i].pos.y, enemyButtons[i].r, 100, color, 1);
		DrawCenterText(enemyButtons[i].pos.x, enemyButtons[i].pos.y,
			context->enemyParty.mons[i].data->Name, GetColor(255, 255, 255), 16.0f);
	}

	// 決定ボタン(3体選択済みの時だけ色を変えて分かるようにする)
	unsigned int confirmColor = (selectedCount == MEMBER_MAX) ? GetColor(0, 200, 0) : GetColor(100, 100, 100);
	DrawCircleAA(confirmButton.pos.x, confirmButton.pos.y, confirmButton.r, 100, confirmColor, 1);
	DrawCenterText(confirmButton.pos.x, confirmButton.pos.y, "戦闘開始", GetColor(255, 255, 255), 20.0f);
}

void PrepMemberStage::Sound()
{
}

bool PrepMemberStage::CursorInParty(int index)
{
	return CheckCircleHit(partyButtons[index].pos, partyButtons[index].r, cursor->GetPos(), 10.0f);
}

bool PrepMemberStage::CursorInConfirm()
{
	return CheckCircleHit(confirmButton.pos, confirmButton.r, cursor->GetPos(), 10.0f);
}

bool PrepMemberStage::IsChosenForBattle(int enemyPartyIndex)
{
	const MonsterBaseData* target = context->enemyParty.mons[enemyPartyIndex].data;
	for (int i = 0; i < MEMBER_MAX; i++)
	{
		if (context->eBattle[i].data == target) return true;
	}
	return false;
}