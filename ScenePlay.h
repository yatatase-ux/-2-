#pragma once
#include "SceneBase.h"
#include "MonsterData.h"
#include "Player.h"
#include "BattleMonster.h"
#include "PhaseManager.h"
#include "BattleContext.h"
#include "InputManager.h"
#include "Party.h"
#include "CpuAttackScorer.h"
#include "PrepStageManager.h"

enum class PlayStage
{
	Preparing,	// 準備段階(6体から3体まで決定)
	Battling	// 戦闘段階
};

class ScenePlay : public SceneBase
{

private:

	std::unique_ptr<PrepStageManager> m_Prep;		// 準備フェーズ用マネージャー
	std::unique_ptr<PhaseManager> m_Battle;			// バトルフェーズ用マネージャー
	PlayStage stage;								// 今が準備かバトルかを判別する変数

	BattleContext context;							// バトルコンテキストの本体

	/// <summary>
	/// 準備完了時の処理
	/// </summary>
	void FinishPreparation();

	/// <summary>
	/// ランダムにCPUのパーティを設定する関数
	/// </summary>
	void GenerateRandomEnemyParty();

public:

	/// <summary>
	/// クラスの基本関数の定義
	/// </summary>
	SCENE_CLASS(ScenePlay);

};