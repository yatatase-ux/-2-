#include "Player.h"

/// <summary>
/// コンストラクタ
/// </summary>
Player::Player()
	: cursor(std::make_unique<Cursor>())
{
}

/// <summary>
/// 入力処理
/// </summary>
void Player::Input()
{
	cursor->Input();
}

/// <summary>
/// 更新処理
/// </summary>
void Player::Update()
{
	cursor->Update();
}

/// <summary>
/// 描画処理
/// </summary>
void Player::Draw()
{
	cursor->Draw();
}

/// <summary>
/// 音声処理
/// </summary>
void Player::Sound()
{
	cursor->Sound();
}

Cursor* Player::GetCursor() const
{
	return cursor.get();
}