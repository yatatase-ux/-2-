#pragma once
#include "Cursor.h"
#include "InputManager.h"
#include "BattleContext.h"

enum class PrepState
{
	None,       // まだ何も選ばれていない(このステージに留まる)
	ToHome,     // Home画面へ(デバッグ時のみ想定)
	ToParty,    // パーティ選出ステージへ
	ToMember,   // メンバー選出ステージへ
	Complete    // 準備完了(3体決定、ScenePlayへ通知)
};

class PrepStageBase
{
protected:
	Cursor* cursor;
	InputManager* input;
	BattleContext* context;
public:

	PrepStageBase(Cursor* arg_cursor, InputManager* arg_input, BattleContext* arg_context)
		: cursor(arg_cursor), input(arg_input), context(arg_context) {}
	virtual ~PrepStageBase() {};

	virtual PrepState Input() = 0;
	virtual PrepState  Update() = 0;
	virtual void Draw() = 0;
	virtual void Sound() = 0;
};

#define PREP_CLASS(className)\
	className(Cursor* arg_cursor, InputManager* arg_input, BattleContext* arg_context);\
	PrepState Input() override;\
	PrepState  Update() override;\
	void Draw() override;\
	void Sound() override;

#define PREP_CONSTRUCTOR(className)\
	className::className(Cursor* arg_cursor, InputManager* arg_input, BattleContext* arg_context)\
		: PrepStageBase(arg_cursor, arg_input, arg_context)

#define PREP_INPUT(className)\
	PrepState className::Input()

#define PREP_UPDATE(className)\
	PrepState  className::Update()
