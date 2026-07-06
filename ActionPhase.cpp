#include "ActionPhase.h"

ActionPhase::ActionPhase(Cursor* arg_cursor, BattleContext* arg_context, InputManager* arg_input)
	: PhaseBase(arg_cursor, arg_context, arg_input)
{
}

PhaseState ActionPhase::Input()
{
	// 行動フェーズでは、入力は不要
	return PhaseState::NONE;
}

PhaseState ActionPhase::Update()
{
	// 行動フェーズの更新処理を実装
	damage.Attack(*context->player, *context->enemy, context->selectedMoveID); // 仮に最初の技を使用する
	return PhaseState::COMMAND;
}

void ActionPhase::Draw()
{
	// 行動フェーズの描画処理を実装
}

void ActionPhase::Sound()
{
	// 行動フェーズの音声処理を実装
}