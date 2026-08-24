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

enum class PlayStage
{
	Preparing,	// 準備段階(6体から3体まで決定)
	Battling	// 戦闘段階
};

class ScenePlay : public SceneBase
{
	BattleMonster pMonster;
	BattleMonster eMonster;	

	BattleMonster pBattle[3];
	Members pMember;

	BattleMonster eBattle[3];
	Members eMember;

//	std::unique_ptr<PrepManager> m_Prep;     // 新規:準備フェーズ用マネージャー
	std::unique_ptr<PhaseManager> m_Battle;
	PlayStage stage;

	BattleContext context;

public:

	SCENE_CLASS(ScenePlay);

	void InitMambers(const MonsterBaseData* mons[], BattleMonster battle[], Members& menber, int count);

};