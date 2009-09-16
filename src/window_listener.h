#ifndef WINDOW_LISTENER_H
#define WINDOW_LISTENER_H

class Window;

class WindowEvent
{
public:
    WindowEvent() : 
        window(NULL), width(-1), height(-1) { }

    WindowEvent(Window* window, INT width = -1, INT height = -1) :
        window(window), width(width), height(height) { }

    Window* window;
    INT width;
    INT height;
};

class WindowListener
{
public:
    virtual ~WindowListener() { };

    virtual void windowClosed(WindowEvent& event);

    virtual void windowResized(WindowEvent& event);

};

#endif