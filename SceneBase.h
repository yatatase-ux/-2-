#pragma once
#include "DxLib.h"
#include "KeyAction.h"
#include "Cursor.h"
#include "InputManager.h"
#include "Player.h"
#include "Party.h" 

enum class SceneState
{
	None,
	OP,
	Play,
	End
};

class SceneBase
{
protected:

	Cursor* cursor;
	InputManager* input;
	Party* playerParty;

public:

	SceneBase(Cursor* arg_cursor, InputManager* arg_input, Party* arg_playerParty)
		:cursor(arg_cursor), input(arg_input), playerParty(arg_playerParty) {};
	virtual SceneState Input() = 0;	// 純粋仮想関数
	virtual SceneState Update() = 0;	// 純粋仮想関数
	virtual void Draw() = 0;	// 純粋仮想関数
	virtual void Sound() = 0;	// 純粋仮想関数
};

#define SCENE_CLASS(className)\
	className(Cursor* arg_cursor, InputManager* arg_input, Party* arg_playerParty);\
	SceneState Input() override;\
	SceneState Update() override;\
	void Draw() override;\
	void Sound() override;

#define SCENE_CONSTRUCTOR(className)\
	className::className(Cursor* arg_cursor, InputManager* arg_input, Party* arg_playerParty)\
			:SceneBase(arg_cursor, arg_input, arg_playerParty)

#define SCENE_INPUT(className)\
	SceneState className::Input()

#define SCENE_UPDATE(className)\
	SceneState className::Update()