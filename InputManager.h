#pragma once
#include "KeyAction.h"

class InputManager
{
private:

    MouseAct mouse;
    KeyAct key;

public:

    MouseAct& Mouse()
    {
        return mouse;
    }

    KeyAct& Key()
    {
        return key;
    }
};