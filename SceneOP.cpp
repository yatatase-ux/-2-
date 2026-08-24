#include "SceneOP.h"

SCENE_CONSTRUCTOR(SceneOP)
{
	// OPシーンの初期化処理
}

SCENE_INPUT(SceneOP)
{
	// OPシーンの入力処理
	bool click = input->Mouse().Push(MOUSE_LEFT);

	if(click)
	{
		return SceneState::Play;	// クリックされたらプレイシーンに遷移
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
	DrawCenterText(WINDOW_W / 2, WINDOW_H / 2, "Click to Start", (255,255,255), 50.0f);
}

void SceneOP::Sound()
{
	// OPシーンの音声再生処理
}