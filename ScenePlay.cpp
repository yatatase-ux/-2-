#include "ScenePlay.h"
#include "RandomUtil.h"
#include "MonsterData.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name=""></param>
SCENE_CONSTRUCTOR(ScenePlay)
{
	BattleHUD::LoadIcons();

	// プレイシーンの初期化処理
	context.playerParty = playerParty;	// SceneBaseが持つポインタをcontextにも渡す(コピーではなく同じ実体を指す)
	EffectApplier effect;
	for (int i = 0; i < PARTY_MAX; i++)
	{
		effect.ResetForNewBattle(context.playerParty->mons[i]);
	}
	
	GenerateRandomEnemyParty();			// CPUの6体をここで確定させる

	stage = PlayStage::Preparing;

	m_Prep = std::make_unique<PrepStageManager>(cursor, input, &context);

	// CPU側の初期化は PrepMemberStage のコンストラクタで行うため、ここでは不要

	image = LoadGraph("data/Monster/1-1.png");
}

ScenePlay::~ScenePlay()
{
	BattleHUD::LoadIcons();
}

/// <summary>
/// 入力処理
/// </summary>
/// <param name=""></param>
SCENE_INPUT(ScenePlay)
{
	// 準備ステージのとき
	if (stage == PlayStage::Preparing)
	{
		if (m_Prep->Input()) // 準備がComplete(完了)したら
		{
			FinishPreparation();
		}
	}
	// バトルステージの時
	else
	{
		m_Battle->Input();
	}
	return SceneState::None;
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name=""></param>
SCENE_UPDATE(ScenePlay)
{
	// INPUTと同じ
	if (stage == PlayStage::Preparing)
	{
		if (m_Prep->Update())
		{
			FinishPreparation();
		}
		return SceneState::None;
	}
	else
	{
		if (m_Battle->Update() == NextScene::ToPrep) 
		{
			ReturnPrep();
		}
		else if (m_Battle->Update() == NextScene::ToEnding) 
		{
			return SceneState::End;
		}

		return SceneState::None;
	}
}

/// <summary>
/// 描画処理
/// </summary>
void ScenePlay::Draw()
{

	// 準備ステージの描画
	if (stage == PlayStage::Preparing)
	{
		m_Prep->Draw();
	}
	// バトルステージの描画
	else
	{
		// プレイシーンの描画処理
		m_Battle->Draw();

		//for (int i = 0; i < MOVE_SLOT_MAX; i++)
		//{
		//	int moveID = context.enemyMoveScore[i].moveID;
		//	const char* moveName = (moveID >= 0) ? MoveTable[moveID].Name : "---"; // 技が無いスロット対策

		//	DrawFormatString(
		//		850,
		//		150 + i * 30,
		//		GetColor(255, 255, 255),
		//		"技:%s, Score:%d",
		//		moveName, context.enemyMoveScore[i].score);
		//}
		//for (int i = 0; i < MEMBER_MAX - 1; i++)
		//{
		//	DrawFormatString(850, 280 + i * 30, GetColor(255, 255, 0),
		//		"交代候補:%s, Score:%d",
		//		context.enemySwitchScore[i].name, context.enemySwitchScore[i].score);
		//}
		//DrawFormatString(850, 400, GetColor(0, 255, 255), "予測:プレイヤーは%s",
		//	context.predictedPlayerDecision.switchToIndex >= 0 ? "交代してくる" : "技を使う");
	}
	FloatXY p = cursor->GetPos();
	DrawFormatString(20, 20, GetColor(255, 255, 255), "x:%f  y:%f", p.x, p.y);
}

/// <summary>
/// 音声処理
/// </summary>
void ScenePlay::Sound()
{

}

void ScenePlay::FinishPreparation()
{
	context.player = context.pMember.Active();
	context.enemy = context.eMember.Active();
	context.player->isRevealed = true;
	context.enemy->isRevealed = true;

	m_Battle = std::make_unique<PhaseManager>(cursor, &context.pMember, &context.eMember, &context, input);
	stage = PlayStage::Battling;
}

void ScenePlay::GenerateRandomEnemyParty()
{
	int chosenIndices[PARTY_MAX];
	PickRandomDistinct(MonsterData::GetCount(), PARTY_MAX, chosenIndices);

	for (int i = 0; i < PARTY_MAX; i++)
	{
		const MonsterBaseData* mons = &MonsterData::GetByIndex(chosenIndices[i]);
		context.enemyParty.mons[i].data = mons;
		context.enemyParty.mons[i].CurrentHP = mons->HP;
		context.enemyParty.mons[i].displayedHP = (float)context.enemyParty.mons[i].CurrentHP;
	}
}

void ScenePlay::ReturnPrep()
{
	context.playerParty = playerParty;

	EffectApplier effect;
	for (int i = 0; i < PARTY_MAX; i++)
	{
		effect.ResetForNewBattle(context.playerParty->mons[i]);
	}

	GenerateRandomEnemyParty();			// CPUの6体をここで確定させる

	stage = PlayStage::Preparing;

	m_Prep = std::make_unique<PrepStageManager>(cursor, input, &context);
}