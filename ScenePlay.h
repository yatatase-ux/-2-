#pragma once
#include "SceneBase.h"
#include "MonsterData.h"
#include "Player.h"
#include "BattleMonster.h"
#include "PhaseManager.h"
#include "BattleContext.h"
#include "InputManager.h"
#include "Party.h"

class ScenePlay : public SceneBase
{
	BattleMonster pMonster;
	BattleMonster eMonster;	

	BattleMonster pBattle[3];
	Members pMember;

	BattleMonster eBattle[3];
	Members eMember;

	std::unique_ptr<Player> player;
	std::unique_ptr<InputManager> m_Input;
	std::unique_ptr<PhaseManager> m_Battle;
	BattleContext context;

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

	void InitMambers(const MonsterBaseData* mons[], BattleMonster battle[], Members& menber, int count);

};