#include "ScenePlay.h"

ScenePlay::ScenePlay()
{
	// プレイシーンの初期化処理
	player = std::make_unique<Player>();
	m_Input = std::make_unique<InputManager>();
	m_Battle = std::make_unique<BattleManager>(player->GetCursor(), &Attack, &Defense, m_Input.get());
}

void ScenePlay::Input()
{
	// プレイシーンの入力処理
	m_Battle->Input();

}

void ScenePlay::Update()
{
	// プレイシーンの更新処理
	player->Update();
	
	m_Battle->Update();
}

void ScenePlay::Draw()
{
	// プレイシーンの描画処理
	m_Battle->Draw();
	player->Draw();
		
	DrawFormatString(
		100,
		300,
		GetColor(255, 255, 255),
		"HP : %d",
		Defense.CurrentHP);
}

void ScenePlay::Sound()
{

}