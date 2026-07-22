#include "CheckWLPhase.h"

PHASE_CONSTRUCTOR(CheckWLPhase)
{

}

PhaseState CheckWLPhase::Input()
{
	return PhaseState::NONE;
}

PhaseState CheckWLPhase::Update()
{
	context->faintedMonster->isFainted = true;

	if (context->faintedMonster == context->enemy)
	{
		// CPU側が瀕死 → 生存怪獣を検索
		int enemy_lose = 0;
		for (int i = 0; i < MEMBER_MAX; i++)
		{
			if (eMembers->mons[i]->isFainted == false)
			{
				context->enemy = eMembers->mons[i];
				return PhaseState::COMMAND;
			}
			enemy_lose++;
		}
		if (enemy_lose >= MEMBER_MAX)
		{
			return PhaseState::GAME_END; // 仮:勝利フェーズへ
		}
	}
	else
	{
		// プレイヤー側が瀕死 → こちらも同様に処理
		int player_lose = 0;
		for (int i = 0; i < MEMBER_MAX; i++)
		{
			if (pMembers->mons[i]->isFainted == false)
			{
				context->player = pMembers->mons[i];
				return PhaseState::COMMAND; // 本来は選択フェーズに飛ばすのが理想
			}
			player_lose++;
		}
		if (player_lose >= MEMBER_MAX)
		{
			return PhaseState::GAME_END; // 仮:敗北フェーズへ
		}
	}
	return PhaseState::NONE;
}

void CheckWLPhase::Draw()
{
	DrawString(500, 250, "Dead Monster", GetColor(255, 255, 255));
}

void CheckWLPhase::Sound()
{

}
