#pragma once
#include <ctime>		// 標準C ライブラリ ヘッダー <time.h> をインクルードし、関連する名前を std 名前空間に追加します。
#include "DxLib.h"		// DxLib
#include "SceneManager.h"

class Game
{
protected:
	SceneManager scene;

public:

	Game() {}

	void GameLoop();

};
