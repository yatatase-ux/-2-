#include "SceneEnd.h"

SCENE_CONSTRUCTOR(SceneEnd)
{
	// エンディングシーンの初期化処理
}

SCENE_INPUT(SceneEnd)
{
	// エンディングシーンの入力処理

	return SceneState::None;
}

SCENE_UPDATE(SceneEnd)
{
	// エンディングシーンの更新処理
}

void SceneEnd::Draw()
{
	// エンディングシーンの描画処理
}

void SceneEnd::Sound()
{
	// エンディングシーンの音声再生処理
}