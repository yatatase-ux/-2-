#include "SceneManager.h"

SceneManager::SceneManager()
{
	nowScene = std::make_unique<SceneOP>();	// 最初のシーンをOPシーンに設定
}

void SceneManager::Input()
{
	nowScene->Input();	// 現在のシーンの入力処理を呼び出す
}

void SceneManager::Update()
{
	nowScene->Update();	// 現在のシーンの更新処理を呼び出す
}

void SceneManager::Draw()
{
	nowScene->Draw();	// 現在のシーンの描画処理を呼び出す
}

void SceneManager::Sound()
{
	nowScene->Sound();	// 現在のシーンの音声再生処理を呼び出す
}
