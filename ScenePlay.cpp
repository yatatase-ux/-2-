#include "ScenePlay.h"

ScenePlay::ScenePlay()
{

	const MonsterBaseData* pData = MonsterData::FindByID(1);
	pMonster.data = pData;
	pMonster.CurrentHP = pData->HP;

	const MonsterBaseData* eData = MonsterData::FindByID(2);
	eMonster.data = eData;
	eMonster.CurrentHP = eData->HP;

	context.player = &pMonster;
	context.enemy = &eMonster;

	// プレイシーンの初期化処理
	player = std::make_unique<Player>();
	m_Input = std::make_unique<InputManager>();
	m_Battle = std::make_unique<BattleManager>(player->GetCursor(), &context, m_Input.get());
}

void ScenePlay::Input()
{
	// プレイシーンの入力処理
	m_Battle->Input();

}

void ScenePlay::Update()
{
	// プレイシーンの更新処理
	player->Update();
	
	m_Battle->Update();
}

void ScenePlay::Draw()
{
	// プレイシーンの描画処理
	m_Battle->Draw();
	player->Draw();
		
	DrawFormatString(
		100,
		300,
		GetColor(255, 255, 255),
		"HP : %d",
		context.enemy->CurrentHP);
}

void ScenePlay::Sound()
{

}