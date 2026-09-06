#include "ActionPhase.h"
#include <cstdio>

PHASE_CONSTRUCTOR(ActionPhase)
{
	turnOrder = turnOrderResolver.Resolve(context, pMembers, eMembers);

	for (int slot = 0; slot < ActionMax; slot++)
	{
		reasoningOnlyLine[slot] = nullptr;
		followUpLine[slot] = nullptr;
		baseLineText[slot][0] = '\0';

		if (turnOrder.isSwitchAction[slot]) continue;
		if (!turnOrder.canAct[slot]) continue;
		if (!turnOrder.willHit[slot]) continue;

		BattleMonster* actor = turnOrder.mons[slot];
		int moveID = turnOrder.moveID[slot];
		sprintf_s(baseLineText[slot], "%sは%sを選択！", actor->data->Name, MoveTable[moveID].Name);
	}

	// 思考可視化(予測ベース)の表示振り分け
	if (context->cpuReasoning != CommentarySituation::None)
	{
		bool cpuIsEarlyer = (turnOrder.mons[Earlyer] == context->enemy);

		if (context->cpuReasoning == CommentarySituation::SwitchMatchingRead)
		{
			// この状況は答え合わせ不要:CPUのターンに理由をそのまま出すだけで完結する
			int cpuSlot = cpuIsEarlyer ? Earlyer : Later;
			reasoningOnlyLine[cpuSlot] = context->cpuReasoningLine;
		}
		else
		{
			// 既存のStayReadingSwitch/SwitchAvoidingThreat(2段階構成)は変更なし
			int playerSlot = cpuIsEarlyer ? Later : Earlyer;
			bool playerActuallySwitched = turnOrder.isSwitchAction[playerSlot];
			int playerActualMoveID = playerActuallySwitched ? -1 : turnOrder.moveID[playerSlot];

			bool hit = commentator.CheckHit(context->cpuReasoning, context->predictedPlayerDecision,
				playerActuallySwitched, playerActualMoveID);

			if (cpuIsEarlyer)
			{
				reasoningOnlyLine[Earlyer] = context->cpuReasoningLine;
			}
			followUpLine[Later] = commentator.PickFollowUpLine(context->cpuReasoning, hit, cpuIsEarlyer);
		}
	}

	time = 120;
	turn = Earlyer;
	turnEnd = false;
	monsDying = false;
	showingStatusResult = false;
}

PhaseState ActionPhase::Input()
{
	return PhaseState::NONE;
}

PhaseState ActionPhase::Update()
{
	ProcessTurn();
	if (monsDying) return PhaseState::CHECK_FAINT;
	if (turnEnd) return PhaseState::COMMAND;
	return PhaseState::NONE;
}

void ActionPhase::Draw()
{
	battleHUD.Draw(*context->player, *context->enemy);

	DrawFillBox(0, 600, WINDOW_W, WINDOW_H, GetColor(75, 75, 75));

	if (showingStatusAnnounce)
	{
		BattleMonster* mon = turnOrder.mons[statusTickIndex];
		bool isBurn = (mon->condition == StatusCondition::Burn);
		presenter.DrawStatusAnnounce(mon->data->Name, isBurn);
		return;
	}

	if (showingStatusResult)
	{
		//if (statusTime > 0)
		//{
		//	presenter.DrawStatusTick(statusResult);
		//}
		return;
	}

	if (time > 0)
	{
		presenter.DrawTurnPreview(turn, turnOrder, moveExecutor,
			baseLineText[turn], reasoningOnlyLine[turn], followUpLine[turn]);
	}
}

void ActionPhase::Sound()
{
}

/// <summary>
/// ターン決定
/// </summary>
void ActionPhase::ProcessTurn()
{
	if (monsDying || turnEnd) return;

	if (showingStatusAnnounce)
	{
		statusAnnounceTime--;
		if (statusAnnounceTime > 0) return;

		showingStatusAnnounce = false;

		// 告知が終わったので、実際にダメージを与える
		BattleMonster* mon = turnOrder.mons[statusTickIndex];
		int dmg = effect.ApplyStatusDamage(*mon);

		statusResult.name[Earlyer] = nullptr;
		statusResult.name[Later] = nullptr;
		statusResult.name[statusTickIndex] = mon->data->Name;
		statusResult.damage[statusTickIndex] = dmg;

		showingStatusResult = true;
		statusTime = 60;
		return;
	}

	// ダメージ数値の表示+アニメーション待ち(既存のshowingStatusResultを、CheckFaintPhaseと同じ「最低表示時間+アニメ完了待ち」の形に書き換え)
	if (showingStatusResult)
	{
		battleHUD.UpdateHPAnimation(*context->player);
		battleHUD.UpdateHPAnimation(*context->enemy);

		statusTime--;
		bool animDone = battleHUD.IsHPAnimDone(*context->player) && battleHUD.IsHPAnimDone(*context->enemy);
		if (statusTime > 0 || !animDone) return;

		showingStatusResult = false;
		ResolveStatusTick(); // 終わったので、次の対象があれば続ける
		return;
	}

	// ダメージ演出待ち:終わるまでは、今の実況(turnに対応するもの)を表示し続けたまま足踏みする
	if (waitingForHPAnim)
	{
		battleHUD.UpdateHPAnimation(*context->player);
		battleHUD.UpdateHPAnimation(*context->enemy);

		if (!battleHUD.IsHPAnimDone(*context->player) || !battleHUD.IsHPAnimDone(*context->enemy))
		{
			return; // まだアニメーション中
		}

		waitingForHPAnim = false;
		AdvanceAfterAction();

		return;
	}

	time--;

	if (turn == Earlyer)
	{
		if (time > 0) return;

		if (!turnOrder.isSwitchAction[Earlyer] && turnOrder.canAct[Earlyer] && turnOrder.willHit[Earlyer])
		{
			moveExecutor.Execute(turnOrder.mons[Earlyer], turnOrder.mons[Later], turnOrder.moveID[Earlyer]);
			waitingForHPAnim = true; // ダメージが発生したので、アニメーション待ちへ(turnはまだ切り替えない)
			return;
		}
		AdvanceAfterAction(); // 交代/まひ/外れの場合はダメージが無いので、そのまま進む
	}
	else // Later
	{
		if (time > 0) return;

		if (!turnOrder.isSwitchAction[Later] && turnOrder.canAct[Later] && turnOrder.willHit[Later])
		{
			moveExecutor.Execute(turnOrder.mons[Later], turnOrder.mons[Earlyer], turnOrder.moveID[Later]);
			waitingForHPAnim = true;
			return;
		}
		AdvanceAfterAction();
	}
}

// 瀕死判定・状態異常処理をまとめる(アニメーション待ちが終わった後、またはダメージが無かった場合に呼ばれる)
void ActionPhase::AdvanceAfterAction()
{
	if (turn == Earlyer)
	{
		monsDying = aftermath.CheckFaint(turnOrder.mons[Later], context);
		time = 120;
		turn = Later;
	}
	else
	{
		monsDying = aftermath.CheckFaint(turnOrder.mons[Earlyer], context);
		if (!monsDying)
		{
			statusTickIndex = Earlyer; // 状態異常チェックを先行から開始
			AdvanceStatusTick();
		}
	}
}

// 次に状態異常を処理すべき対象を探し、あれば告知を始める
void ActionPhase::AdvanceStatusTick()
{
	while (statusTickIndex < ActionMax)
	{
		BattleMonster* mon = turnOrder.mons[statusTickIndex];
		if (mon->condition == StatusCondition::Poison || mon->condition == StatusCondition::Burn)
		{
			showingStatusAnnounce = true;
			statusAnnounceTime = 60; // 「どくだ！」を見せる時間
			return;
		}
		statusTickIndex++; // この対象は対象外、次へ
	}

	// 両方チェックし終えた
	statusTickIndex = -1;
	turnEnd = true;
}

// ダメージのアニメーションが終わった後、次の対象があれば続ける
void ActionPhase::ResolveStatusTick()
{
	BattleMonster* mon = turnOrder.mons[statusTickIndex];
	if (mon->CurrentHP <= 0)
	{
		monsDying = true;
		context->faintedMonster = mon;
	}

	statusTickIndex++;
	AdvanceStatusTick();
}