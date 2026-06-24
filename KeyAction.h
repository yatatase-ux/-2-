#pragma once
#include "DxLib.h"

const int USE_KEY_MAX = 1;

enum {
	SPACE
};

class KeyAct
{
protected:

	int key_type[USE_KEY_MAX] =
	{
		KEY_INPUT_UP
	};

	bool key_sw[USE_KEY_MAX] = { false };

public:

	/// <summary>
	/// 短押し
	/// </summary>
	/// <param name="KeyCode">キー</param>
	/// <returns></returns>
	int Push(int KeyCode)
	{
		if (CheckHitKey(key_type[KeyCode]))
		{
			if (key_sw[KeyCode] == false)
			{
				key_sw[KeyCode] = true;
				return true;
			}
		}
		else
		{
			key_sw[KeyCode] = false;
		}

		return false;
	}

	/// <summary>
	/// 長押し
	/// </summary>
	/// <param name="KeyCode">キー</param>
	/// <returns></returns>
	int Check(int KeyCode)
	{
		if (CheckHitKey(key_type[KeyCode]))
		{
			return true;

		}

		return false;
	}

};
