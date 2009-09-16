#ifndef KEYBOARD_LISTENER_H
#define KEYBOARD_LISTENER_H

#include "common.h"

class Window;

class KeyEvent
{
public:
    KeyEvent() : 
        window(NULL), keyCode(-1), repeat(-1) { }
    KeyEvent(Window* window, INT keyCode, INT repeat = -1) :
        window(window), keyCode(keyCode), repeat(repeat) { }

    Window* window;
    INT keyCode;
    INT repeat;
};

class KeyboardListener
{
public:
    virtual ~KeyboardListener() { };

    virtual void keyPressed(KeyEvent& event);
    virtual void keyReleased(KeyEvent& event);

};

#endif