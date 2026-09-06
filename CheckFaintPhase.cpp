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

    // 瀕死になった側のパーティに、まだ他の生存がいるか先に確認する
    bool isPlayerFainted = (context->faintedMonster == context->player);    // 先に瀕死になったのがプレイヤーか
    Members* target = isPlayerFainted ? pMembers : eMembers;                // 該当するメンバーを代入
    bool sideStillAlive = false;
    for (int i = 0; i < MEMBER_MAX; i++)
    {
        if (!target->mons[i]->isFainted) { sideStillAlive = true; break; }  // 1体でも生存してたらフラグを立ててループを抜ける
    }

    // 試合がここで終わる場合は、生存側の状態異常処理は行わない
    // 終了：False　続行：True
    if (sideStillAlive)
    {
        // 倒れていない方(まだ場に残っている方)の状態異常を処理する
        // 倒れたのがプレイヤーならCPU、逆ならプレイヤーをsurvivor(サバイバー:生存者)へ
        BattleMonster* survivor = (context->faintedMonster == context->player) ? context->enemy : context->player;
        
        // 生存側が毒か火傷なら
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

                // もし状態異常ダメージによって倒れたら
                if (survivor->CurrentHP <= 0)
                {
                    survivor->isFainted = true;

                    if (isPlayerFainted)
                    {
                        // 生存していたCPU側も倒れた場合:プレイヤーの新しい選択を待たず、
                        // 公平性のためこの時点で先にCPU側の交代先を決めてしまう
                        for (int i = 0; i < MEMBER_MAX; i++)
                        {
                            if (!eMembers->mons[i]->isFainted)
                            {
                                context->pendingEnemyNext = eMembers->mons[i];  // 代入先が変わっただけ
                                break;
                            }
                        }
                    }
                    else
                    {
                        // 生存していたプレイヤー側が倒れた場合、プレイヤーの選択(UI操作)が必要なので予約する
                        context->secondFaintedMonster = survivor;
                    }
                }

                return PhaseState::NONE;
            }
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
        BattleMonster* nextEnemy = eMembers->mons[aliveIndex];

        // CPU側の選出が終わった直後に、予約されている瀕死が無いか確認する
        if (context->secondFaintedMonster != nullptr)
        {
            // 連鎖している場合、公開はプレイヤーの選択が終わるタイミングまで待つ
            context->pendingEnemyNext = nextEnemy;

            context->faintedMonster = context->secondFaintedMonster;
            context->secondFaintedMonster = nullptr;
            return PhaseState::CHECK_FAINT;
        }

        // 連鎖が無い、通常の単独瀕死ならこれまで通り即座に公開する
        context->enemy = nextEnemy;
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
