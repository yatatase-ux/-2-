#include "ScenePlay.h"

SCENE_CONSTRUCTOR(ScenePlay)
{
	// プレイシーンの初期化処理
	
	// 戦闘参加怪獣の設定
	const MonsterBaseData* pMons[3] = { MonsterData::FindByID(1),
										MonsterData::FindByID(5), 
										MonsterData::FindByID(9) };

	const MonsterBaseData* eMons[3] = { MonsterData::FindByID(17),
										MonsterData::FindByID(4), 
										MonsterData::FindByID(12) };

	InitMambers(pMons, pBattle, pMember, MEMBER_MAX);			// プレイヤーのパーティ初期化
	InitMambers(eMons, eBattle, eMember, MEMBER_MAX);			// CPUのパーティ初期化
	context.player = pMember.Active();							// プレイヤーの現在のモンスターをBattleContextに設定
	context.enemy = eMember.Active();							// CPUの現在のモンスターをBattleContextに設定
	context.player->isRevealed = true;							// プレイヤーのモンスターは初期状態で場に出ているので、isRevealedをtrueに設定
	context.enemy->isRevealed = true;							// CPUのモンスターも同様にisRevealedをtrueに設定
	

	stage = PlayStage::Preparing;

	// フェーズ管理マネージャークラスの初期化
//	m_Prep = std::make_unique<PrepStageManager>(cursor, input, &context);
	m_Battle = std::make_unique<PhaseManager>(cursor, &pMember, &eMember, &context, input);
}

SCENE_INPUT(ScenePlay)
{
	// プレイシーンの入力処理
	m_Battle->Input();

	return SceneState::None;
}

SCENE_UPDATE(ScenePlay)
{
	// プレイシーンの更新処理
	if (stage == PlayStage::Preparing)
	{
		//if (m_Prep->Update()) // 準備完了(6→3体まで決定)でtrueを返す想定
		//{
		//	// 確定したメンバーでパーティを構築してから、戦闘フェーズへ切り替え
		//	InitMambers(...);
		//	context.player = pMember.Active();
		//	context.enemy = eMember.Active();
			m_Battle = std::make_unique<PhaseManager>(cursor, &pMember, &eMember, &context, input);
		//	stage = PlayStage::Battling;
		//}
		return SceneState::None;
	}
	else
	{
		if (m_Battle->Update()) return SceneState::End;
		return SceneState::None;
	}
	return SceneState::None;
}

void ScenePlay::Draw()
{
	// プレイシーンの描画処理
	m_Battle->Draw();

	//CPU
	DrawFormatString(
		1100,
		100,
		GetColor(255, 255, 255),
		"HP : %d",
		context.enemy->CurrentHP);
	DrawString(900, 70, context.enemy->data->Name, GetColor(255, 255, 255));
	for (int i = 0; i < MOVE_SLOT_MAX; i++)
	{
		int moveID = context.enemyMoveScore[i].moveID;
		const char* moveName = (moveID >= 0) ? MoveTable[moveID].Name : "---"; // 技が無いスロット対策

		DrawFormatString(
			850,
			150 + i * 30,
			GetColor(255, 255, 255),
			"技:%s, Score:%d",
			moveName, context.enemyMoveScore[i].score);
	}
	for (int i = 0; i < MEMBER_MAX - 1; i++)
	{
		DrawFormatString(850, 280 + i * 30, GetColor(255, 255, 0),
			"交代候補:%s, Score:%d",
			context.enemySwitchScore[i].name, context.enemySwitchScore[i].score);
	}

	//Player
	DrawFormatString(
		100,
		400,
		GetColor(255, 255, 255),
		"HP : %d",
		context.player->CurrentHP);
	DrawString(100, 430, context.player->data->Name, GetColor(255, 255, 255));
	DrawFormatString(
		100,
		500,
		GetColor(255, 255, 255),
		"物理攻撃ランク : %d",
		context.player->PATKRank);
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