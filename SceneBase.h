#pragma once
#include "DxLib.h"

class SceneBase
{
public:

	virtual ~SceneBase() {}
	virtual void Input() = 0;	// 純粋仮想関数
	virtual void Update() = 0;	// 純粋仮想関数
	virtual void Draw() = 0;	// 純粋仮想関数
	virtual void Sound() = 0;	// 純粋仮想関数
};