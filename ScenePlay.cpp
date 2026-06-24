#include "ScenePlay.h"

ScenePlay::ScenePlay()
{
	// プレイシーンの初期化処理
	player = std::make_unique<Player>();
	ui = std::make_unique<ButtleUI>(player->GetCursor());
}

void ScenePlay::Input()
{
	// プレイシーンの入力処理
}

void ScenePlay::Update()
{
	// プレイシーンの更新処理
	ui->Update();
	player->Update();
}

void ScenePlay::Draw()
{
	// プレイシーンの描画処理
	ui->Draw();
	player->Draw();
}

void ScenePlay::Sound()
{
	// プレイシーンの音声再生処理
}