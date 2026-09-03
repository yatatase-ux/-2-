#include "CommandPhase.h"
#include "MonsterBaseData.h"

PHASE_CONSTRUCTOR(CommandPhase),
fightButton(1150.0f, 425.0f, 75.0f, "たたかう", GetColor(175, 0, 0), GetColor(255, 0, 0)),
changeButton(1150.0f, 600.0f, 75.0f, "交代", GetColor(0, 175, 0), GetColor(0, 255, 0))
{
	// プレイヤーの技選択状態を初期化(このターンまだ何も選んでいない状態にする)
	context->player->selectedMoveID = -1;

	// 双方の生存数から、それぞれの視点で「試合を決める場面か」を先に判定しておく
	bool isMatchPointForPlayer = CheckMatchPoint(eMembers); // プレイヤー視点:CPU側の残りが1体か
	bool isMatchPoint = CheckMatchPoint(pMembers);           // CPU視点:プレイヤー側の残りが1体か

	// ① プレイヤー行動の予測を行い、他フェーズからも参照できるよう context にも保存
	CpuDecisionResult predicted = PredictPlayerAction(isMatchPointForPlayer);
	context->predictedPlayerDecision = predicted;

	// ② ①の予測結果を反映させて、CPU自身の行動を決定する
	CpuDecisionResult decision = DecideCpuAction(predicted, isMatchPoint);

	// ③ ②の結果と①の予測を照らし合わせて、実況の理由を判定・記録する
	DetermineCommentary(decision, predicted);

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
	battleHUD.Draw(*context->player, *context->enemy);

	fightButton.Draw();
	changeButton.Draw();
}

void CommandPhase::Sound()
{
}
// 指定されたパーティの生存数を数え、残り1体以下かどうかを返す
bool CommandPhase::CheckMatchPoint(Members* members)
{
	int aliveCount = 0;
	for (int i = 0; i < MEMBER_MAX; i++)
		if (!members->mons[i]->isFainted) aliveCount++;
	return (aliveCount <= 1);
}

// selfとopponentを入れ替えて cpuBrain.Decide を呼ぶことで、
// 「もしプレイヤーがCPUと同じ思考回路だったら、今ターン何を選ぶか」を算出する
CpuDecisionResult CommandPhase::PredictPlayerAction(bool isMatchPointForPlayer)
{
	CpuEvalContext predictCtx{ *context->player, *context->enemy, *pMembers, *eMembers, damage, isMatchPointForPlayer };
	return cpuBrain.Decide(predictCtx);
}

// ①の予測結果を反映させてCPU自身の行動を評価し、実際に決定を確定させる
CpuDecisionResult CommandPhase::DecideCpuAction(const CpuDecisionResult& predicted, bool isMatchPoint)
{
	bool predictedPlayerWillSwitch = (predicted.switchToIndex >= 0);

	CpuEvalContext ctx{ *context->enemy, *context->player, *eMembers, *pMembers, damage, isMatchPoint };
	ctx.opponentPredictedToSwitch = predictedPlayerWillSwitch;
	ctx.predictedOpponentDecision = &predicted;
	CpuDecisionResult decision = cpuBrain.Decide(ctx);

	// デバッグ表示用に、技・交代それぞれのスコアを保存しておく
	for (int i = 0; i < MOVE_SLOT_MAX; i++) context->enemyMoveScore[i] = decision.moveScores[i];
	for (int i = 0; i < MEMBER_MAX - 1; i++) context->enemySwitchScore[i] = decision.switchScores[i];

	// CPUの実際の行動を確定させる(交代 or 技)
	// ※ ここではまだ context->enemy のポインタ自体は差し替わらない(実際の差し替えはActionPhase側で行う)
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

	return decision;
}

// CPUの決定理由を判定し、実況として記録する
void CommandPhase::DetermineCommentary(const CpuDecisionResult& decision, const CpuDecisionResult& predicted)
{
	// context->enemy はこの時点でもまだ「交代前の(これから退く)個体」を指している
	// (②の中で changeMonster フィールドは設定されたが、ポインタ自体はまだ差し替わっていないため)
	context->cpuReasoning = commentator.ClassifyReasoning(decision, predicted,
		*context->enemy, *pMembers, damage, context->cpuReasoningLine, sizeof(context->cpuReasoningLine));

	// 予測に基づく理由(交代読み関連)が何も見つからなかった場合のみ、
	// 「危険を承知で先制技を選んだか(LastStand)」を追加でチェックする
	if (context->cpuReasoning == CommentarySituation::None && decision.selectedMoveID >= 0)
	{
		if (commentator.CheckLastStand(*context->enemy, *context->player, decision.selectedMoveID, damage))
		{
			context->cpuReasoning = CommentarySituation::LastStand;
			strcpy_s(context->cpuReasoningLine, commentator.PickLastStandLine());
		}
	}
}