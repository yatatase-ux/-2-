#include "BattleManager.h"

BattleManager::BattleManager(BattleUI* arg_ui, BattleMonster* arg_attacker, BattleMonster* arg_defender)
	: ui(arg_ui), attacker(arg_attacker), defender(arg_defender)
{
	phase = std::make_unique<CommandPhase>(ui, attacker, defender);
}

/// <summary>
/// 入力処理
/// </summary>
void BattleManager::Input()
{
	PhaseState change_phase = phase->Input();
	currentPhase = change_phase;

	ChangePhase(change_phase);

	DrawPhaseForDebug(currentPhase);
}

/// <summary>
/// 更新処理
/// </summary>
void BattleManager::Update()
{
	phase->Update();
}

/// <summary>
/// 描画処理
/// </summary>
void BattleManager::Draw()
{
	phase->Draw();
}

/// <summary>
/// サウンド処理
/// </summary>
void BattleManager::Sound()
{
	phase->Sound();
}

void BattleManager::ChangePhase(PhaseState nextPhase)
{
	if (nextPhase == PhaseState::NONE)
	{
		return;
	}
	phase = CreatePhase(nextPhase);
}

std::unique_ptr<PhaseBase> BattleManager::CreatePhase(PhaseState state)
{
	switch (state)
	{
	case PhaseState::COMMAND:
		return std::make_unique<CommandPhase>(ui, attacker, defender);

	case PhaseState::MOVE_SELECT:
		return std::make_unique<MoveSelectPhase>(ui, attacker, defender);
	}

	return nullptr;
}

void BattleManager::DrawPhaseForDebug(PhaseState phase)
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
	}
}