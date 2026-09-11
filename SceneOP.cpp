#include "SceneOP.h"

SCENE_CONSTRUCTOR(SceneOP)
{
	// OPシーンの初期化処理
	BG = LoadGraph("data/BG/OP.jpg");
	clickMessa = LoadGraph("data/BG/LCtS.png");

	timer = 50;
}

SceneOP::~SceneOP()
{
	DeleteGraph(BG);
	DeleteGraph(clickMessa);
}

SCENE_INPUT(SceneOP)
{
	// OPシーンの入力処理
	bool click = input->Mouse().Push(MOUSE_LEFT);

	if(click)
	{
		return SceneState::Play;	// クリックされたらプレイシーンに遷移
	}

	timer--;
	if (timer < 0)
	{
		timer = 40;
	}

	return SceneState::None;
}

SCENE_UPDATE(SceneOP)
{
	// OPシーンの更新処理


	return SceneState::None;
}

void SceneOP::Draw()
{
	// OPシーンの描画処理
	DrawExtendGraph(0, 0, WINDOW_W, WINDOW_H, BG, TRUE);
	if(timer > 10)
	{
		DrawRotaGraph(WINDOW_W / 2, WINDOW_H / 2 + 125, 0.4f, 0.0, clickMessa, TRUE);
	}
}

void SceneOP::Sound()
{
	// OPシーンの音声再生処理
}