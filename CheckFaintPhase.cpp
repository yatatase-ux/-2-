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
    // 生存側の状態異常ダメージを表示中なら、それが終わるまで待つ
    if (showingSurvivorStatusTick)
    {
        // 状態異常ダメージのアニメーションを、この表示時間中に進める
        battleHUD.UpdateHPAnimation(*context->player);
        battleHUD.UpdateHPAnimation(*context->enemy);

        survivorStatusTime--;
        bool animDone = battleHUD.IsHPAnimDone(*context->player) && battleHUD.IsHPAnimDone(*context->enemy);

        // 表示時間が残っているか、アニメーションがまだ終わっていなければ待つ
        if (survivorStatusTime > 0 || !animDone) return PhaseState::NONE;

        showingSurvivorStatusTick = false;
        return ResolveOutcome();
    }

    // 2秒間表示させておく
    time--;
    if (time >= 0) return PhaseState::NONE;

    // 怪獣が倒れたフラッグをTRUEにする
    context->faintedMonster->isFainted = true;

    // 倒れていない方(まだ場に残っている方)の状態異常を処理する
    BattleMonster* survivor = (context->faintedMonster == context->player) ? context->enemy : context->player;
    if (survivor->condition == StatusCondition::Poison || survivor->condition == StatusCondition::Burn)
    {
        // 片方が瀕死になったときのもう片方の状態異常処理
        int dmg = effect.ApplyStatusDamage(*survivor);
        if (dmg > 0)
        {
            survivorStatusName = survivor->data->Name;
            survivorStatusDamage = dmg;
            showingSurvivorStatusTick = true;
            survivorStatusTime = 90; // 表示時間（秒）
            return PhaseState::NONE;
        }
    }

    return ResolveOutcome(); // 状態異常が無ければ、これまで通りすぐに判定
}

/// <summary>
/// 通常の瀕死後処理
/// </summary>
/// <returns>次のフェーズ</returns>
PhaseState CheckFaintPhase::ResolveOutcome()
{
    bool isPlayerFainted = (context->faintedMonster == context->player);    // プレイヤーが瀕死になったら
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
        context->isPlayerWin = !isPlayerFainted;
        return PhaseState::GAME_END;
    }

    if (isPlayerFainted)
    {
        context->isForcedSwitch = true;
        return PhaseState::CHANGE_MONS;
    }
    else
    {
        context->enemy = eMembers->mons[aliveIndex];
        effect.ResetBattleRanks(*context->enemy);
        context->enemy->isRevealed = true;
        return PhaseState::COMMAND;
    }
}

void CheckFaintPhase::Draw()
{
    // 背景を暗くして文字を見やすくする
    DrawFillBox(0, 600, WINDOW_W, WINDOW_H, GetColor(75, 75, 75));

    battleHUD.Draw(*context->player, *context->enemy);

    if (showingSurvivorStatusTick)
    {
        // 生存側の状態異常ダメージメッセージ
        DrawFillBox(0, 600, WINDOW_W, WINDOW_H, GetColor(75, 75, 75));
        DrawCenterFormatText(WINDOW_W / 2, WINDOW_H - 60, GetColor(255, 255, 0), 30,
            "%s は状態異常のダメージ：%d", survivorStatusName, survivorStatusDamage);
    }
    else
    {
        DrawFillBox(0, 600, WINDOW_W, WINDOW_H, GetColor(75, 75, 75));
        DrawCenterFormatText(WINDOW_W / 2, WINDOW_H - 60, GetColor(255, 255, 0), 30,
            "%s、戦闘不能！", context->faintedMonster->data->Name);
    }
}

void CheckFaintPhase::Sound()
{

}
