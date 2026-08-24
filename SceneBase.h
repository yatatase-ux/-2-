#pragma once
#include "DxLib.h"
#include "KeyAction.h"
#include "Cursor.h"
#include "InputManager.h"
#include "Player.h"

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

public:

	SceneBase(Cursor* arg_cursor, InputManager* arg_input)
		:cursor(arg_cursor), input(arg_input){};
	virtual ~SceneBase() {}
	virtual SceneState Input() = 0;	// 純粋仮想関数
	virtual SceneState Update() = 0;	// 純粋仮想関数
	virtual void Draw() = 0;	// 純粋仮想関数
	virtual void Sound() = 0;	// 純粋仮想関数
};

#define SCENE_CLASS(className)\
	className(Cursor* arg_cursor, InputManager* arg_input);\
	SceneState Input() override;\
	SceneState Update() override;\
	void Draw() override;\
	void Sound() override;

#define SCENE_CONSTRUCTOR(className)\
	className::className(Cursor* arg_cursor, InputManager* arg_input)\
			:SceneBase(arg_cursor, arg_input)\

#define SCENE_INPUT(className)\
	SceneState className::Input()

#define SCENE_UPDATE(className)\
	SceneState className::Update()