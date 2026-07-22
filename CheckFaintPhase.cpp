#include "CheckFaintPhase.h"

PHASE_CONSTRUCTOR(CheckFaintPhase)
{

}

PhaseState CheckFaintPhase::Input()
{
	return PhaseState::NONE;
}

PhaseState CheckFaintPhase::Update()
{
    context->faintedMonster->isFainted = true;

    bool isPlayerFainted = (context->faintedMonster == context->player);
    Members* target = isPlayerFainted ? pMembers : eMembers;

    int aliveCount = 0;
    int aliveIndex = -1;
    for (int i = 0; i < MEMBER_MAX; i++)
    {
        if (!target->mons[i]->isFainted)
        {
            aliveCount++;
            if (aliveIndex < 0) aliveIndex = i;
        }
    }

    if (aliveCount == 0)
    {
        context->isPlayerWin = !isPlayerFainted; // 勝敗をcontextに記録
        return PhaseState::GAME_END;
    }

    if (isPlayerFainted)
    {
        context->isForcedSwitch = true;
        return PhaseState::CHANGE_MONS;
    }
    else
    {
        // 暫定:生存先頭を出す。将来的にCPU選出ロジックに差し替え
        context->enemy = eMembers->mons[aliveIndex];
        return PhaseState::COMMAND;
    }
}

void CheckFaintPhase::Draw()
{
	DrawString(500, 250, "Dead Monster", GetColor(255, 255, 255));
}

void CheckFaintPhase::Sound()
{

}
