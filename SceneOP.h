#pragma once
#include "SceneBase.h"
#include "Function.h"

class SceneOP : public SceneBase
{
protected:

	KeyAct key;

	int BG;
	int clickMessa;

	int timer;

public:

	SCENE_CLASS(SceneOP);

};