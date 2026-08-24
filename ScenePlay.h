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

class ScenePlay : public SceneBase
{
	BattleMonster pMonster;
	BattleMonster eMonster;	

	BattleMonster pBattle[3];
	Members pMember;

	BattleMonster eBattle[3];
	Members eMember;

	std::unique_ptr<PhaseManager> m_Battle;
	BattleContext context;

public:

	SCENE_CLASS(ScenePlay);

	void InitMambers(const MonsterBaseData* mons[], BattleMonster battle[], Members& menber, int count);

};