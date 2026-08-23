#pragma once
#include <iostream>
#include <memory>
#include "SceneOP.h"
#include "ScenePlay.h"
#include "SceneEnd.h"
#include "KeyAction.h"
#include "InputManager.h"

enum class Scene
{
	OP,
	Play,
	End,

	Max
};

class SceneManager
{
protected:

	std::unique_ptr<SceneBase> nowScene;	// 現在のシーンを管理するためのスマートポインタ

	Scene scene;

	KeyAct key;

	std::unique_ptr<InputManager> m_Input;

public:

	SceneManager();

	void Input();

	void Update();

	void Draw();

	void Sound();

	void SceneChange(Scene now_scene);

};
