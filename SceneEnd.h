#pragma once
#include "SceneBase.h"

class SceneEnd : public SceneBase
{

public:

	SceneEnd();

	/// <summary>
	/// “ü—Íˆ—
	/// </summary>
	void Input() override;
	/// <summary>
	/// XVˆ—
	/// </summary>
	void Update() override;

	/// <summary>
	/// •`‰æˆ—
	/// </summary>
	void Draw() override;

	/// <summary>
	/// ‰¹ºÄ¶ˆ—
	/// </summary>
	void Sound() override;
};