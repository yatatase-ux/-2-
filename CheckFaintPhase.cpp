#include "CheckFaintPhase.h"
#include "Function.h"

PHASE_CONSTRUCTOR(CheckFaintPhase)
{
    time = 120;
}

PhaseState CheckFaintPhase::Input()
{
	return PhaseState::NONE;
}

PhaseState CheckFaintPhase::Update()
{
    time--;
    if (time >= 0) return PhaseState::NONE;
    
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

	// もしプレイヤーのモンスターが瀕死になった場合、強制交代フラグを立てる
    if (isPlayerFainted)
    {
        context->isForcedSwitch = true;
        return PhaseState::CHANGE_MONS;
    }
	// もしCPUのモンスターが瀕死になった場合、次の生存モンスターを自動で選出する
    else
    {
        // 暫定:生存先頭を出す。将来的にCPU選出ロジックに差し替え
		context->enemy = eMembers->mons[aliveIndex];    // 次の生存モンスターを選出する
        effect.ResetBattleRanks(*context->enemy);	    // ランクをリセットする
		context->enemy->isRevealed = true;              // 場に出たことにする
        return PhaseState::COMMAND;
    }

}

void CheckFaintPhase::Draw()
{
    battleHUD.Draw(*context->player, *context->enemy);

    DrawFillBox(0, 600, WINDOW_W, WINDOW_H, GetColor(75, 75, 75));
    DrawCenterFormatText(WINDOW_W / 2, WINDOW_H - 60, GetColor(255, 255, 0), 30,
        "%s、戦闘不能！", context->faintedMonster->data->Name);
//	DrawString(500, 250, "Dead Monster", GetColor(255, 255, 255));
}

void CheckFaintPhase::Sound()
{

}
