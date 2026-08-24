#include "SceneEnd.h"

SCENE_CONSTRUCTOR(SceneEnd)
{
	// エンディングシーンの初期化処理
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
	DrawCenterText(WINDOW_W / 2, WINDOW_H / 2, "FINISH", GetColor(255, 0, 0), 50.0f);
	return SceneState::None;
}

void SceneEnd::Draw()
{
	// エンディングシーンの描画処理
}

void SceneEnd::Sound()
{
	// エンディングシーンの音声再生処理
}