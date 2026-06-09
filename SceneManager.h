#pragma once
#include <iostream>
#include "SceneOP.h"
#include "ScenePlay.h"
#include "SceneEnd.h"

class SceneManager
{
protected:

	std::unique_ptr<SceneBase> nowScene;	// 現在のシーンを管理するためのスマートポインタ

public:

	SceneManager();

	void Input();

	void Update();

	void Draw();

	void Sound();

};
