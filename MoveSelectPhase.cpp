#include "MoveSelectPhase.h"
#include "Function.h"

PHASE_CONSTRUCTOR(MoveSelectPhase)
{
	for (int i = 0; i < MOVE_SLOT_MAX; i++)
	{
		float x = 1000.0f;
		float y = 350.0f + i * 85.0f;
		int moveID = context->player->data->MoveID[i];

		const char* label = (moveID >= 0) ? MoveTable[moveID].Name : "";
		moveButtons[i] = Button(x, y, 250.0f, 75.0f, label, GetColor(0, 200, 255), GetColor(0, 255, 255));

		if (moveID < 0)
		{
			moveButtons[i].SetDisabled(true); // 空スロットは押せないようにする
		}
	}
}

PhaseState MoveSelectPhase::Input()
{
	if (input->Mouse().Push(MOUSE_RIGHT)) return PhaseState::COMMAND;

	// SHIFTを押している間は、詳細表示の切り替えだけを行う(通常の技選択はさせない)
	if (input->Key().Check(SHIFT))
	{
		for (int i = 0; i < MOVE_SLOT_MAX; i++)
		{
			if (moveButtons[i].Input(cursor, input)) // Pushはここで1回だけ呼ばれる
			{
				if (detailMoveIndex == i)
				{
					// 同じボタンをもう一度押した:閉じる
					moveButtons[i].SetSelected(false);
					detailMoveIndex = -1;
				}
				else
				{
					// 別のボタンに切り替える:前のハイライトを消して、新しい方をハイライト
					if (detailMoveIndex >= 0) moveButtons[detailMoveIndex].SetSelected(false);
					moveButtons[i].SetSelected(true);
					detailMoveIndex = i;
				}
				return PhaseState::NONE;
			}
		}
		return PhaseState::NONE; // SHIFT押下中は、以降の通常選択処理には進ませない
	}

	for (int i = 0; i < MOVE_SLOT_MAX; i++)
	{
		if (moveButtons[i].Input(cursor, input))
		{
			context->player->selectedMoveID = context->player->data->MoveID[i];
			return PhaseState::ACTION;
		}
	}
	return PhaseState::NONE;
}

PhaseState MoveSelectPhase::Update()
{
	for (int i = 0; i < MOVE_SLOT_MAX; i++)
	{
		moveButtons[i].Update(cursor);
	}
	return PhaseState::NONE;
} 

void MoveSelectPhase::Draw()
{
	for (int i = 0; i < MOVE_SLOT_MAX; i++)
	{
		moveButtons[i].Draw();
	}

	if (detailMoveIndex >= 0)
	{
		int moveID = context->player->data->MoveID[detailMoveIndex];
		// 矩形パネル(空いている左側のスペースに配置)
		DrawFillBox(100, 150, 950, 470, GetColor(50, 100, 180));
		moveDetail.Draw(MoveTable[moveID], 150.0f, 180.0f);
	}
}

void MoveSelectPhase::Sound()
{
}