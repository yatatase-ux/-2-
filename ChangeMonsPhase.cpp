#include "ChangeMonsPhase.h"

PHASE_CONSTRUCTOR(ChangeMonsPhase),
buttons{
	Button(1000.0f, 350.0f, 250.0f, 75.0f, pMembers->mons[0]->data->Name, GetColor(200,200,200), GetColor(255,255,255)),
	Button(1000.0f, 435.0f, 250.0f, 75.0f, pMembers->mons[1]->data->Name, GetColor(200,200,200), GetColor(255,255,255)),
	Button(1000.0f, 520.0f, 250.0f, 75.0f, pMembers->mons[2]->data->Name, GetColor(200,200,200), GetColor(255,255,255))
}
{
	// コンストラクタの時点でも瀕死状態を反映しておく(1フレーム目の入力判定のため)
	for (int i = 0; i < 3; i++)
	{
		buttons[i].SetDisabled(pMembers->mons[i]->isFainted);
	}
}

PhaseState ChangeMonsPhase::Input()
{
	// 技詳細が開いている間は、右クリックで閉じる操作だけを受け付ける(一番内側の層)
	if (showingMoveDetail)
	{
		if (input->Mouse().Push(MOUSE_RIGHT))
		{
			showingMoveDetail = false;
		}
		return PhaseState::NONE;
	}

	if (!context->isForcedSwitch && input->Mouse().Push(MOUSE_RIGHT))
		return PhaseState::COMMAND;

	// 怪獣詳細が開いている間、技ボックスへのクリックを優先的にチェックする
	if (detailIndex >= 0)
	{
		FloatXY boxPos, boxSize;
		for (int i = 0; i < MOVE_SLOT_MAX; i++)
		{
			// カーソルが乗っている時だけPushを呼ぶ(短絡評価で、乗っていなければPush自体呼ばれない)
			if (monsterDetail.GetMoveBoxRect(i, detailBoxStart.x, detailBoxStart.y, detailBoxEnd.x, detailBoxEnd.y, boxPos, boxSize)
				&& CheckPointBoxHit(cursor->GetPos(), boxPos, boxSize)
				&& input->Mouse().Push(MOUSE_LEFT))
			{
				int moveID = pMembers->mons[detailIndex]->data->MoveID[i];
				if (moveID >= 0)
				{
					detailMoveID = moveID;
					showingMoveDetail = true;
				}
				return PhaseState::NONE;
			}
		}
	}

	// SHIFT+左クリックで、怪獣詳細を切り替える
	if (input->Key().Check(SHIFT))
	{
		for (int i = 0; i < MEMBER_MAX; i++)
		{
			if (buttons[i].Input(cursor, input))
			{
				if (detailIndex == i)
				{
					buttons[i].SetSelected(false);
					detailIndex = -1;
				}
				else
				{
					if (detailIndex >= 0) buttons[detailIndex].SetSelected(false);
					buttons[i].SetSelected(true);
					detailIndex = i;
				}
				return PhaseState::NONE;
			}
		}
		return PhaseState::NONE;
	}

	// 通常の交代選択処理
	for (int i = 0; i < MEMBER_MAX; i++)
	{
		if (buttons[i].Input(cursor, input))
		{
			if (context->isForcedSwitch)
			{
				context->player = pMembers->mons[i];
				context->isForcedSwitch = false;
				return PhaseState::COMMAND;
			}
			context->player->changeMonster = i;
			return PhaseState::ACTION;
		}
	}
	return PhaseState::NONE;
}

PhaseState ChangeMonsPhase::Update()
{
	for (int i = 0; i < 3; i++)
	{
		buttons[i].SetDisabled(pMembers->mons[i]->isFainted);
		buttons[i].Update(cursor);
	}
	return PhaseState::NONE;
}

void ChangeMonsPhase::Draw()
{
	for (int i = 0; i < MEMBER_MAX; i++)
	{
		buttons[i].Draw();
	}

	if (detailIndex >= 0)
	{
		const MonsterBaseData* data = pMembers->mons[detailIndex]->data;

		DrawFillBox(detailBoxStart.x, detailBoxStart.y, detailBoxEnd.x, detailBoxEnd.y, GetColor(50, 100, 180));
		monsterDetail.Draw(*data, detailBoxStart.x, detailBoxStart.y, detailBoxEnd.x, detailBoxEnd.y);

		if (showingMoveDetail)
		{
			DrawFillBox(150, 150, 800, 450, GetColor(220, 220, 220)); // 仮座標
			moveDetail.Draw(MoveTable[detailMoveID], 180.0f, 180.0f);
		}
	}
}

void ChangeMonsPhase::Sound()
{

}