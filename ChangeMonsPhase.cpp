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
	if (!context->isForcedSwitch && input->Mouse().Push(MOUSE_RIGHT))
		return PhaseState::COMMAND;

	// SHIFTを押している間は、詳細表示の切り替えだけを行う(通常の交代選択はさせない)
	if (input->Key().Check(SHIFT))
	{
		for (int i = 0; i < MEMBER_MAX; i++)
		{
			if (buttons[i].Input(cursor, input)) // Pushはここで1回だけ呼ばれる
			{
				if (detailIndex == i)
				{
					// 同じボタンをもう一度押した:閉じる
					buttons[i].SetSelected(false);
					detailIndex = -1;
				}
				else
				{
					// 別のボタンに切り替える
					if (detailIndex >= 0) buttons[detailIndex].SetSelected(false);
					buttons[i].SetSelected(true);
					detailIndex = i;
				}
				return PhaseState::NONE;
			}
		}
		return PhaseState::NONE; // SHIFT押下中は、以降の通常選択処理には進ませない
	}

	for (int i = 0; i < 3; i++)
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
	for (int i = 0; i < 3; i++)
	{
		buttons[i].Draw();
	}

	if (detailIndex >= 0)
	{
		const MonsterBaseData* data = pMembers->mons[detailIndex]->data;
		// 赤い丸があった範囲に合わせて配置
		DrawFillBox(50, 50, 900, 650, GetColor(50, 100, 180));
		monsterDetail.Draw(*data, 50, 50, 900, 650);
	}
}

void ChangeMonsPhase::Sound()
{

}