#pragma once
#include "SceneBase.h"
#include "MonsterData.h"
#include "Player.h"
#include "DamageCalculator.h"
#include "BattleMonster.h"
#include "BattleManager.h"

class ScenePlay : public SceneBase
{
	MonsterData mons;

	std::unique_ptr<Player> player;

	std::unique_ptr<BattleManager> BM;



	MonsterBaseData attacker =
	{
		1,
		"モンスター",
		{Type::Normal, Type::None},
		80,80,80,80,80,80,
		{0,-1,-1,-1}
	};
	MonsterBaseData defender =
	{
		2,
		"雑魚",
		{Type::Normal, Type::None},
		300,300,300,300,30,300,
		{0,-1,-1,-1}
	};
	BattleMonster Attack =
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