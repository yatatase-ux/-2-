#include "ScenePlay.h"

ScenePlay::ScenePlay()
{
	// プレイシーンの初期化処理
	
	// 戦闘参加怪獣の設定
	const MonsterBaseData* pMons[3] = { MonsterData::FindByID(2),
										MonsterData::FindByID(3), 
										MonsterData::FindByID(4) };

	const MonsterBaseData* eMons[3] = { MonsterData::FindByID(2),
										MonsterData::FindByID(3), 
										MonsterData::FindByID(4) };
	InitMambers(pMons, pBattle, pMember, MEMBER_MAX);
	InitMambers(eMons, eBattle, eMember, MEMBER_MAX);
	context.player = pMember.Active();
	context.enemy = eMember.Active();
	
	// プレイヤークラスの初期化
	player = std::make_unique<Player>();
	// 入力関係クラスの初期化
	m_Input = std::make_unique<InputManager>();
	// フェーズ管理マネージャークラスの初期化
	m_Battle = std::make_unique<PhaseManager>(player->GetCursor(), &pMember, &eMember, &context, m_Input.get());
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
		1100,
		100,
		GetColor(255, 255, 255),
		"HP : %d",
		context.enemy->CurrentHP);
	DrawString(1100, 70, context.enemy->data->Name, GetColor(255,255,255));

	DrawFormatString(
		100,
		400,
		GetColor(255, 255, 255),
		"HP : %d",
		context.player->CurrentHP);
	DrawString(100, 430, context.player->data->Name, GetColor(255, 255, 255));
}

void ScenePlay::Sound()
{

}

void ScenePlay::InitMambers(const MonsterBaseData* mons[], BattleMonster battle[], Members& member, int count)
{
	for (int i = 0; i < count; i++)
	{
		battle[i].data = mons[i];
		battle[i].CurrentHP = mons[i]->HP;

		member.mons[i] = &battle[i];
	}
}