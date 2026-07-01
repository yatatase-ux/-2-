#include "CommandPhase.h"

CommandPhase::CommandPhase()
{
	
}

/// <summary>
/// “ü—Íˆ—
/// </summary>
void CommandPhase::Input()
{
	BUI.Input();
}

/// <summary>
/// XVˆ—
/// </summary>
void CommandPhase::Update()
{
	BUI.Update();
}

/// <summary>
/// •`‰æˆ—
/// </summary>
void CommandPhase::Draw()
{
	BUI.Draw();
}

/// <summary>
/// ‰¹ºˆ—
/// </summary>
void CommandPhase::Sound()
{
	BUI.Sound();
}