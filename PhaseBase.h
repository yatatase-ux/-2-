#pragma once
#include "DxLib.h"

class PhaseBase
{
protected:

public:

	PhaseBase() {}

	~PhaseBase() {}

	virtual void Input() = 0;

	virtual void Update() = 0;

	virtual void Draw() = 0;

	virtual void Sound() = 0;
};