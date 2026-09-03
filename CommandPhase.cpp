#include "CommandPhase.h"
#include "MonsterBaseData.h"

PHASE_CONSTRUCTOR(CommandPhase),
fightButton(1150.0f, 425.0f, 75.0f, "たたかう", GetColor(175, 0, 0), GetColor(255, 0, 0)),
changeButton(1150.0f, 600.0f, 75.0f, "交代", GetColor(0, 175, 0), GetColor(0, 255, 0))
{
	// プレイヤーの技選択状態を初期化(このターンまだ何も選んでいない状態にする)
	context->player->selectedMoveID = -1;

	// プレイヤー側パーティの生存数を数える
	// (相手=CPUにとって、これを倒せば「試合を決める撃破」になるかどうかの判定に使う)
	int aliveCount = 0;
	for (int i = 0; i < MEMBER_MAX; i++)
		if (!pMembers->mons[i]->isFainted) aliveCount++;
	bool isMatchPoint = (aliveCount <= 1);

	// CPU側パーティの生存数を数える
	// (プレイヤー側の予測行動を評価する際、「プレイヤーにとって試合を決める場面か」の判定に使う)
	int enemyAliveCount = 0;
	for (int i = 0; i < MEMBER_MAX; i++)
		if (!eMembers->mons[i]->isFainted) enemyAliveCount++;
	bool isMatchPointForPlayer = (enemyAliveCount <= 1);

	// ① プレイヤー行動の予測
	// selfとopponentを入れ替えて cpuBrain.Decide を呼ぶことで、
	// 「もしプレイヤーがCPUと同じ思考回路だったら、今ターン何を選ぶか」を算出する
	CpuEvalContext predictCtx{ *context->player, *context->enemy, *pMembers, *eMembers, damage, isMatchPointForPlayer };
	context->predictedPlayerDecision = cpuBrain.Decide(predictCtx);
	bool predictedPlayerWillSwitch = (context->predictedPlayerDecision.switchToIndex >= 0);

	// ② CPU自身の決定(①の予測結果を反映させて評価する)
	CpuEvalContext ctx{ *context->enemy, *context->player, *eMembers, *pMembers, damage, isMatchPoint };
	ctx.opponentPredictedToSwitch = predictedPlayerWillSwitch;
	ctx.predictedOpponentDecision = &context->predictedPlayerDecision;
	CpuDecisionResult decision = cpuBrain.Decide(ctx);

	// デバッグ表示用に、技・交代それぞれのスコアを保存しておく
	for (int i = 0; i < MOVE_SLOT_MAX; i++) context->enemyMoveScore[i] = decision.moveScores[i];
	for (int i = 0; i < MEMBER_MAX - 1; i++) context->enemySwitchScore[i] = decision.switchScores[i];

	// ③ 実況:CPUの決定理由を判定・記録する
	// context->enemy はこの時点ではまだ「交代前の(これから退く)個体」を指しているため、
	// SwitchAvoidingThreat の判定(退く個体が予測技に弱いか)がここで正しく行える
	context->cpuReasoning = commentator.ClassifyReasoning(decision, context->predictedPlayerDecision,
		*context->enemy, *pMembers, damage, context->cpuReasoningLine, sizeof(context->cpuReasoningLine));

	// 予測に基づく理由(交代読み関連)が何も見つからなかった場合のみ、
	// 「危険を承知で先制技を選んだか(LastStand)」を追加でチェックする
	// ※ decision.selectedMoveID は、CPUが交代ではなく技を選んだ場合のみ有効な値になっている
	if (context->cpuReasoning == CommentarySituation::None && decision.selectedMoveID >= 0)
	{
		if (commentator.CheckLastStand(*context->enemy, *context->player, decision.selectedMoveID, damage))
		{
			context->cpuReasoning = CommentarySituation::LastStand;
			strcpy_s(context->cpuReasoningLine, commentator.PickLastStandLine());
		}
	}

	// ④ CPUの実際の行動を確定させる(交代 or 技)
	if (decision.switchToIndex >= 0)
	{
		context->enemy->changeMonster = decision.switchToIndex;
		context->enemy->selectedMoveID = -1;
	}
	else
	{
		context->enemy->selectedMoveID = decision.selectedMoveID;
		context->enemy->changeMonster = -1;
	}

	context->player->changeMonster = -1;
}

PhaseState CommandPhase::Input()
{
	if (fightButton.Input(cursor, input)) return PhaseState::MOVE_SELECT;
	if (changeButton.Input(cursor, input)) return PhaseState::CHANGE_MONS;
	return PhaseState::NONE;
}

PhaseState CommandPhase::Update()
{
	fightButton.Update(cursor);
	changeButton.Update(cursor);
	return PhaseState::NONE;
}

void CommandPhase::Draw()
{
	fightButton.Draw();
	changeButton.Draw();
}

void CommandPhase::Sound()
{
}