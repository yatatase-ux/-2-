#include "SceneManager.h"

SceneManager::SceneManager()
{
	nowScene = std::make_unique<ScenePlay>();	// 最初のシーンをOPシーンに設定

	scene = Scene::OP;
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

void SceneManager::SceneChange(Scene now_scene)
{
	switch (now_scene)
	{
	case Scene::OP:
		nowScene = std::make_unique<ScenePlay>();
		scene = Scene::Play;
		break;

	case Scene::Play:
		nowScene = std::make_unique<SceneEnd>();
		scene = Scene::End;
		break;

	case Scene::End:
		nowScene = std::make_unique<SceneOP>();
		scene = Scene::OP;
		break;
	}
}