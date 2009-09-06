#ifndef KEYBOARD_LISTENER_H
#define KEYBOARD_LISTENER_H

#include "common.h"

class Window;

class KeyboardListener
{
public:
    virtual ~KeyboardListener() { };

    virtual void keyDown(Window* window, INT keyCode, INT repeat);
    virtual void keyUp(Window* window, INT keyCode);

};

#endif