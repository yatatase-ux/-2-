#include "ActionPhase.h"

PHASE_CONSTRUCTOR(ActionPhase)
{
	// 行動順を決定する
	turnOrder = turnOrderResolver.Resolve(context, pMembers, eMembers);

	// CPU側の攻撃技選択にのみ実況を生成(1回だけ)
	for (int slot = 0; slot < ActionMax; slot++)
	{
		reactionLine[slot] = nullptr;
		baseLineText[slot][0] = '\0';

		if (turnOrder.isSwitchAction[slot]) continue; // 交代は既存の「→交代」表示のまま
		if (!turnOrder.canAct[slot]) continue;         // まひは既存表示のまま
		if (!turnOrder.willHit[slot]) continue;        // 外れは既存表示のまま

		int otherSlot = (slot == Earlyer) ? Later : Earlyer;
		BattleMonster* actor = turnOrder.mons[slot];
		BattleMonster* target = turnOrder.mons[otherSlot];
		int moveID = turnOrder.moveID[slot];

		sprintf_s(baseLineText[slot], "%sは%sを選択！", actor->data->Name, MoveTable[moveID].Name);

		bool isMatchPoint = (actor == context->enemy)
			? (CountAlive(pMembers) <= 1)
			: (CountAlive(eMembers) <= 1);

		reactionLine[slot] = commentator.Comment(*actor, *target, moveID, isMatchPoint);
	}

	time = 120;						// ターン処理の時間を設定する
	turn = Earlyer;					// 先攻の処理から開始する
	turnEnd = false;				// ターン終了フラグを初期化する
	monsDying = false;				// 瀕死判定フラグを初期化する
	showingStatusResult = false;	// 継続ダメージ表示フラグを初期化する
}

PhaseState ActionPhase::Input()
{
	return PhaseState::NONE;
}

PhaseState ActionPhase::Update()
{
	ProcessTurn();									// ターン処理を進める
	if (monsDying) return PhaseState::CHECK_FAINT;	// 瀕死判定が発生した場合、CHECK_FAINTフェーズに移行する
	if (turnEnd) return PhaseState::COMMAND;		// ターン終了時、次のターンに移行するためCOMMANDフェーズに移行する
	
	return PhaseState::NONE;						
}

void ActionPhase::Draw()
{
	if (showingStatusResult)
	{
		if (statusTime > 0)
		{
			presenter.DrawStatusTick(statusResult);
		}
		return;
	}

	if (time > 0)
	{
		presenter.DrawTurnPreview(turn, turnOrder, moveExecutor,
									baseLineText[turn], reactionLine[turn]);
	}
}

void ActionPhase::Sound()
{

}

int ActionPhase::CountAlive(Members* members)
{
	int count = 0;
	for (int i = 0; i < MEMBER_MAX; i++)
	{
		if (!members->mons[i]->isFainted) count++;
	}
	return count;
}

/// <summary>
/// ターン処理を進める
/// </summary>
void ActionPhase::ProcessTurn()
{
	// 継続ダメージ表示中は、時間経過のみでターン処理を進めない
	if (showingStatusResult)
	{
		statusTime--;						// 継続ダメージ表示時間を減らす
		if (statusTime <= 0)	// 継続ダメージ表示が終わったら、ターン終了フラグを立てる
		{
			showingStatusResult = false;	// 継続ダメージ表示終了
			turnEnd = true;					// ターン終了フラグを立てる
		}
		return;
	}
	// ターン処理の時間経過
	time--;

	// 先攻の処理
	if (turn == Earlyer)
	{
		if (time <= 0)
		{
			// 先攻が交代でなく、行動可能で、技が命中する場合
			if (!turnOrder.isSwitchAction[Earlyer] && turnOrder.canAct[Earlyer] && turnOrder.willHit[Earlyer]) 
			{
				// 先攻の技を実行する
				moveExecutor.Execute(turnOrder.mons[Earlyer], turnOrder.mons[Later], turnOrder.moveID[Earlyer]);
			}
			// 先攻のモンスターが瀕死になったかをチェックする
			monsDying = aftermath.CheckFaint(turnOrder.mons[Later], context);
			time = 120;	// 後攻の処理に移るため、時間をリセットする
			turn = Later;	// 後攻の処理に移る
		}
	}
	// 後攻の処理
	else // turn == Later
	{
		if (time <= 0)
		{
			// 後攻が交代でなく、行動可能で、技が命中する場合
			if (!turnOrder.isSwitchAction[Later] && turnOrder.canAct[Later] && turnOrder.willHit[Later])
			{
				// 後攻の技を実行する
				moveExecutor.Execute(turnOrder.mons[Later], turnOrder.mons[Earlyer], turnOrder.moveID[Later]);
			}
			// 後攻のモンスターが瀕死になったかをチェックする
			monsDying = aftermath.CheckFaint(turnOrder.mons[Earlyer], context);

			// ターン終了時の継続ダメージ処理を行う
			if (!monsDying)
			{
				// ターン終了時の継続ダメージ処理を行う
				statusResult = aftermath.ProcessEndOfTurn(turnOrder.mons, context);	

				// 継続ダメージで瀕死になった場合 
				if (statusResult.causedFaint) 
				{
					// 瀕死になったモンスターがいる場合、monsDyingフラグを立てる
					monsDying = true;
				}
				// 継続ダメージを受けたモンスターがいる場合、継続ダメージ表示フラグを立てる
				else if (statusResult.name[Earlyer] != nullptr || statusResult.name[Later] != nullptr)
				{
					showingStatusResult = true;	// 継続ダメージ表示フラグを立てる
					statusTime = 60;			// 継続ダメージ表示時間を設定する
				}
				// 継続ダメージで瀕死になったモンスターもおらず、継続ダメージを受けたモンスターもいない場合、ターン終了フラグを立てる
				else
				{
					turnEnd = true;
				}
			}
		}
	}
}