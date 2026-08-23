#pragma once
#include "DxLib.h"
#include "KeyAction.h"
#include "Cursor.h"

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

public:

	SceneBase(Cursor* arg_cursor)
		:cursor(arg_cursor){};
	~SceneBase() {}
	virtual SceneState Input() = 0;	// 純粋仮想関数
	virtual void Update() = 0;	// 純粋仮想関数
	virtual void Draw() = 0;	// 純粋仮想関数
	virtual void Sound() = 0;	// 純粋仮想関数
};

#define SCENE_CLASS(className)\
	className(Cursor* arg_cursor);\
	SceneState Input() override;\
	void Update() override;\
	void Draw() override;\
	void Sound() override;

#define SCENE_CONSTRUCTOR(className)\
	className::className()

#define SCENE_INPUT(className)\
	SceneState className::Input()

#define SCENE_UPDATE(className)\
	void className::Update()