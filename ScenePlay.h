#pragma once
#include "SceneBase.h"
#include "MonsterData.h"
#include "Player.h"
#include "BattleUI.h"
#include "BattleManager.h"
#include "BattleMonster.h"

class ScenePlay : public SceneBase
{
	MonsterData mons;

	std::unique_ptr<Player> player;

	std::unique_ptr<BattleUI> ui;

	BattleManager BM;

	MonsterBaseData attacker =
	{
		1,
		"モンスター",
		{Element::NORMAL, Element::NONE},
		80,80,80,80,80,80,
		{0,-1,-1,-1}
	};

	MonsterBaseData defender =
	{
		2,
		"雑魚",
		{Element::NORMAL, Element::NONE},
		30,30,30,30,30,30,
		{0,-1,-1,-1}
	};

	BattleMonster Atttack =
	{
		&attacker,
		attacker.HP,
		0, 0, 0, 0, 0
	};
	BattleMonster Defense =
	{
		&defender,
		defender.HP,
		0, 0, 0, 0, 0
	};

public:

	ScenePlay();

	/// <summary>
	/// 入力処理
	/// </summary>
	void Input() override;
	/// <summary>
	/// 更新処理
	/// </summary>
	void Update() override;

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw() override;

	/// <summary>
	/// 音声再生処理
	/// </summary>
	void Sound() override;
};