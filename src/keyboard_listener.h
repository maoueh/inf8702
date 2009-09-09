// TODO Need a KeyboardEvent

#ifndef KEYBOARD_LISTENER_H
#define KEYBOARD_LISTENER_H

#include "common.h"

class Window;

class KeyboardListener
{
public:
    virtual ~KeyboardListener() { };

    virtual void keyPressed(Window* window, INT keyCode, INT repeat);
    virtual void keyReleased(Window* window, INT keyCode);

};

#endif