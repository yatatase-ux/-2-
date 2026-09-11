#pragma once
#include "PrepStageBase.h"
#include "Button.h"
#include "MemberDetail.h"
#include "Structure.h"

class PrepMemberStage : public PrepStageBase
{
private:

	int memberOrder[PARTY_MAX];		// 各パーティ枠が何番目に選ばれたか(-1:未選択)
	int selectedCount = 0;			// 選択済みの数(0～3)
	Button partyButtons[PARTY_MAX];	// 自分の6体
	Button enemyButtons[PARTY_MAX]; // CPUの6体(表示のみ)
	Button confirmButton;			// 戦闘開始ボタン

	FloatXY ImagePos[2][6] ={
	{	// [0] プレイヤー側
		{150.0f, 520.0f}, 
		{310.0f, 520.0f}, 
		{470.0f, 520.0f}, 
		{630.0f, 520.0f}, 
		{790.0f, 520.0f}, 
		{950.0f, 520.0f} 
		},
	{	// [1] CPU側
		{150.0f, 150.0f}, 
		{310.0f, 150.0f}, 
		{470.0f, 150.0f}, 
		{630.0f, 150.0f}, 
		{790.0f, 150.0f}, 
		{950.0f, 150.0f} } 
	};





	MemberDetail memberDetail;
	const MonsterBaseData* detailTarget = nullptr; // nullptrなら非表示

	PrepState DetailInput();

public:

	PREP_CLASS(PrepMemberStage);

};