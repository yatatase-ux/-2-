#include "BattleManager.h"

BattleManager::BattleManager(BattleUI* ui, BattleMonster* attacker, BattleMonster* defender)
{
	phase = std::make_unique<CommandPhase>(ui, attacker, defender);
}

/// <summary>
/// 入力処理
/// </summary>
void BattleManager::Input()
{
	phase->Input();
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