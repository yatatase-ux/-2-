#include "PhaseManager.h"

PhaseManager::PhaseManager(Cursor* arg_cursor, BattleContext* arg_context, InputManager* arg_input)
	: cursor(arg_cursor), context(arg_context), input(arg_input)
{
	phase = std::make_unique<CommandPhase>(cursor, context, input);
}

/// <summary>
/// 入力処理
/// </summary>
void PhaseManager::Input()
{
	PhaseState change_phase = phase->Input();

	ChangePhase(change_phase);

	DrawPhaseForDebug(currentPhase);
}

/// <summary>
/// 更新処理
/// </summary>
void PhaseManager::Update()
{
	//phase->Update();

	PhaseState change_phase = phase->Update();

	ChangePhase(change_phase);
}

/// <summary>
/// 描画処理
/// </summary>
void PhaseManager::Draw()
{
	phase->Draw();
}

/// <summary>
/// サウンド処理
/// </summary>
void PhaseManager::Sound()
{
	phase->Sound();
}

void PhaseManager::ChangePhase(PhaseState nextPhase)
{
	if (nextPhase == PhaseState::NONE)
	{
		return;
	}
	phase = CreatePhase(nextPhase);
}

std::unique_ptr<PhaseBase> PhaseManager::CreatePhase(PhaseState state)
{
	switch (state)
	{
	case PhaseState::COMMAND:
		currentPhase = PhaseState::COMMAND;
		return std::make_unique<CommandPhase>(cursor, context, input);

	case PhaseState::MOVE_SELECT:
		currentPhase = PhaseState::MOVE_SELECT;
		return std::make_unique<MoveSelectPhase>(cursor, context, input);

	case PhaseState::ACTION:
		currentPhase = PhaseState::ACTION;
		return std::make_unique<ActionPhase>(cursor, context, input);
		
	case PhaseState::CHECK_FAINT:
		return std::make_unique<CheckWLPhase>(cursor, context, input);
	}

	return nullptr;
}

void PhaseManager::DrawPhaseForDebug(PhaseState phase)
{
	switch (phase)
	{
	case PhaseState::NONE:
		DrawFormatString(20, 20, GetColor(255, 255, 255), "Phase: NONE");
		break;
	case PhaseState::COMMAND:
		DrawFormatString(20, 20, GetColor(255, 255, 255), "Phase: COMMAND");
		break;
	case PhaseState::MOVE_SELECT:
		DrawFormatString(20, 20, GetColor(255, 255, 255), "Phase: MOVE_SELECT");
		break;
	case PhaseState::ACTION:
		DrawFormatString(20, 20, GetColor(255, 255, 255), "Phase: ACTION");
		break;
	case PhaseState::CHECK_FAINT:
		DrawFormatString(20, 20, GetColor(255, 255, 255), "Phase: CehckWin-Lose");
		break;
	}
}