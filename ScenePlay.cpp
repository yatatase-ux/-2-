#include "ScenePlay.h"

ScenePlay::ScenePlay()
{
	// プレイシーンの初期化処理
	player = std::make_unique<Player>();
	ui = std::make_unique<BattleUI>(player->GetCursor());
}

void ScenePlay::Input()
{
	// プレイシーンの入力処理
	ui->Input();

	if (ui->InputButtom(Fight))
	{
		int damage =
			BM.CalcDamage(
				attacker,
				defender,
				0);

		Defense.CurrentHP -= damage;

	}

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

	
	DrawFormatString(
		100,
		300,
		GetColor(255, 255, 255),
		"Damage : %d",
		Defense.CurrentHP);
}

void ScenePlay::Sound()
{
	// プレイシーンの音声再生処理
}