#include "SceneEnd.h"

SCENE_CONSTRUCTOR(SceneEnd)
{
	// エンディングシーンの初期化処理
	BG = LoadGraph("data/BG/EDBG.jpg");
}

SceneEnd::~SceneEnd()
{
	DeleteGraph(BG);
}

SCENE_INPUT(SceneEnd)
{
	// エンディングシーンの入力処理
	bool click = input->Mouse().Push(MOUSE_LEFT);
	if(click)
	{
		return SceneState::OP;	// クリックされたらOPシーンに遷移
	}


	return SceneState::None;
}

SCENE_UPDATE(SceneEnd)
{
	// エンディングシーンの更新処理
	return SceneState::None;
}

void SceneEnd::Draw()
{
	// エンディングシーンの描画処理
	DrawExtendGraph(0, 0, WINDOW_W, WINDOW_H, BG, TRUE);
}

void SceneEnd::Sound()
{
	// エンディングシーンの音声再生処理
}