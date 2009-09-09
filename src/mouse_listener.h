// TODO Need a MouseEvent

#ifndef MOUSE_LISTENER_H
#define MOUSE_LISTENER_H

#include "common.h"

#define MOUSE_BUTTON_LEFT   0
#define MOUSE_BUTTON_MIDDLE 1
#define MOUSE_BUTTON_RIGHT  2

class Window;

class MouseListener
{
public:
    virtual ~MouseListener() { };

    virtual void mousePressed(Window* window, INT button, INT x, INT y);
    virtual void mouseReleased(Window* window, INT button, INT x, INT y);
    virtual void mouseDoubleClicked(Window* window, INT button, INT x, INT y);

    virtual void mouseMoved(Window* window, INT x, INT y);
    virtual void mouseDragged(Window* window, INT x, INT y);

    virtual void mouseWheel(Window* window, INT x, INT y);

};

#endif