// TODO Need a WindowEvent

#ifndef WINDOW_LISTENER_H
#define WINDOW_LISTENER_H

class Window;

class WindowListener
{
public:
    virtual ~WindowListener() { };

    virtual void windowClosed(Window* window);

    virtual void windowResized(Window* window, INT width, INT height);

};

#endif