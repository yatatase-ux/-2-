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
	ui->Input();

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

	int damage =
		BM.CalcDamage(
			attacker,
			defender,
			0);
	DrawFormatString(
		100,
		300,
		GetColor(255, 255, 255),
		"Damage : %d",
		damage);
}

void ScenePlay::Sound()
{
	// プレイシーンの音声再生処理
}