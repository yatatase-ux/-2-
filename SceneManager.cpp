#include "SceneManager.h"

SceneManager::SceneManager()
{
	player = std::make_unique<Player>();
	m_Input = std::make_unique<InputManager>();
	nowScene = std::make_unique<SceneOP>(player->GetCursor(), m_Input.get(), &playerParty);	// 最初のシーンをOPシーンに設定

	scene = Scene::OP;
}

void SceneManager::Input()
{
	SceneState now_scene = nowScene->Input();	// 現在のシーンの入力処理を呼び出す
	SceneChange(now_scene);	// 現在のシーンの入力処理の結果に応じてシーン遷移を行う
	player->Input();	// プレイヤーの入力処理を呼び出す
}

void SceneManager::Update()
{
	SceneState now_scene = nowScene->Update();	// 現在のシーンの更新処理を呼び出す
	SceneChange(now_scene);	// 現在のシーンの更新処理の結果に応じてシーン遷移を行う
	player->Update();	// プレイヤーの更新処理を呼び出す
}

void SceneManager::Draw()
{
	nowScene->Draw();	// 現在のシーンの描画処理を呼び出す
	player->Draw();	// プレイヤーの描画処理を呼び出す
}

void SceneManager::Sound()
{
	nowScene->Sound();	// 現在のシーンの音声再生処理を呼び出す
	player->Sound();	// プレイヤーの音声再生処理を呼び出す
}

void SceneManager::SceneChange(SceneState now_scene)
{
	if(now_scene == SceneState::None)
	{
		return;	// シーン遷移がない場合は何もしない
	}

	CreateScene(now_scene);
}

void SceneManager::CreateScene(SceneState now_scene)
{
	switch (now_scene)
	{
	case SceneState::OP:
		nowScene = std::make_unique<SceneOP>(player->GetCursor(), m_Input.get(), &playerParty); // 追加
		scene = Scene::OP;
		break;
	case SceneState::Play:
		nowScene = std::make_unique<ScenePlay>(player->GetCursor(), m_Input.get(), &playerParty); // 追加
		scene = Scene::Play;
		break;
	case SceneState::End:
		nowScene = std::make_unique<SceneEnd>(player->GetCursor(), m_Input.get(), &playerParty); // 追加
		scene = Scene::End;
		break;
	}
}