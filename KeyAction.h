#pragma once
#include "DxLib.h"

const int USE_KEY_MAX = 1;

enum {
	SPACE,
};

class KeyAct
{
protected:

	int key_type[USE_KEY_MAX] =
	{
		KEY_INPUT_UP,
	};

	bool key_sw[USE_KEY_MAX] = { false};

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

const int MOUSE_KEY_MAX = 2;

enum {
	MOUSE_LEFT,
	MOUSE_RIGHT
};

class MouseAct
{

protected:

	int key_type[MOUSE_KEY_MAX] =
	{
		MOUSE_INPUT_LEFT,
		MOUSE_INPUT_RIGHT
	};

	bool key_sw[MOUSE_KEY_MAX] = { false, false };

public:

	/// <summary>
	/// 短押し
	/// </summary>
	/// <param name="MouseInput">キー</param>
	/// <returns></returns>
	int Push(int MouseInput)
	{
		if ((GetMouseInput() & key_type[MouseInput]) != 0)
		{
			if (key_sw[MouseInput] == false)
			{
				key_sw[MouseInput] = true;
				return true;
			}
		}
		else
		{
			key_sw[MouseInput] = false;
		}

		return false;
	}

	/// <summary>
	/// 長押し
	/// </summary>
	/// <param name="MouseInput">キー</param>
	/// <returns></returns>
	int Check(int MouseInput)
	{
		if ((GetMouseInput() & key_type[MouseInput]) != 0)
		{
			return true;

		}

		return false;
	}

};