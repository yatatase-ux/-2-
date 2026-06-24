#pragma once
#include "SceneBase.h"
#include "MonsterData.h"
#include "Player.h"
#include "ButtleUI.h"

class ScenePlay : public SceneBase
{
	MonsterData mons;

	std::unique_ptr<Player> player;

	std::unique_ptr<ButtleUI> ui;

public:

	ScenePlay();

	/// <summary>
	/// “ü—Íˆ—
	/// </summary>
	void Input() override;
	/// <summary>
	/// XVˆ—
	/// </summary>
	void Update() override;

	/// <summary>
	/// •`‰æˆ—
	/// </summary>
	void Draw() override;

	/// <summary>
	/// ‰¹ºÄ¶ˆ—
	/// </summary>
	void Sound() override;
};