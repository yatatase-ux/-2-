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
}

void ChangeMonsPhase::Sound()
{

}