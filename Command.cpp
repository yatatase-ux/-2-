#include "CommandPhase.h"

CommandPhase::CommandPhase(BattleUI* ui, BattleMonster* attacker, BattleMonster* defender)
	: PhaseBase(ui, attacker, defender)
{
	
}

/// <summary>
/// “ü—Íˆ—
/// </summary>
PhaseState CommandPhase::Input()
{
	ui->Input();

	if(ui->InputButton(Fight))
	{
		return PhaseState::MOVE_SELECT;
	}

	return PhaseState::NONE;
}

/// <summary>
/// XVˆ—
/// </summary>
void CommandPhase::Update()
{
	ui->Update();
}

/// <summary>
/// •`‰æˆ—
/// </summary>
void CommandPhase::Draw()
{
	ui->Draw();
}

/// <summary>
/// ‰¹ºˆ—
/// </summary>
void CommandPhase::Sound()
{
	ui->Sound();
}
