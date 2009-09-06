#ifndef WINDOW_LISTENER_H
#define WINDOW_LISTENER_H

class Window;

class WindowListener
{
public:
    virtual ~WindowListener() { };

    virtual void  windowClosed(Window* window);

};

#endif