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

    virtual void mousePressed(Window* window, INT button);
    virtual void mouseReleased(Window* window, INT button);
    virtual void mouseDoubleClicked(Window* window, INT button);

    virtual void mouseMoved(Window* window);
    virtual void mouseDragged(Window* window);

    virtual void mouseWheel(Window* window);

};

#endif